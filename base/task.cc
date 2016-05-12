#include "base/task.h"

#include <glog/logging.h>

using std::bind;
using std::function;
using std::lock_guard;
using std::make_shared;
using std::mutex;
using std::ostream;
using std::placeholders::_1;
using std::shared_ptr;
using std::unique_lock;
using std::vector;

namespace mpr_pgw {


Task::Task(const function<void(Task*)>& done_callback, Executor* executor)
    : done_callback_(done_callback),
      executor_(CHECK_NOTNULL(executor)),
      state_(ACTIVE),
      cancelled_(false),
      holds_(0) {
}


Task::~Task() {
  CHECK_EQ(state_, DONE);
  CHECK(cancel_callbacks_.empty());
}


void Task::Cancel() {
  unique_lock<mutex> lock(lock_);

  if (state_ == DONE || cancelled_) {
    return;
  }

  cancelled_ = true;

  vector<function<void()>> cancel_callbacks;
  cancel_callbacks_.swap(cancel_callbacks);

  holds_ += cancel_callbacks.size();
  const vector<shared_ptr<Task>> child_tasks(child_tasks_);

  lock.unlock();

  for (const auto& child_task : child_tasks) {
    child_task->Cancel();
  }

  for (const auto& cb : cancel_callbacks) {
    executor_->Add(bind(&Task::RunCancelCallback, this, cb));
  }
}


Status Task::status() const {
  lock_guard<mutex> lock(lock_);
  CHECK_NE(state_, ACTIVE);
  return status_;
}


bool Task::Return(const Status& status) {
  unique_lock<mutex> lock(lock_);

  if (state_ != ACTIVE) {
    return false;
  }

  status_ = status;
  state_ = PREPARED;
  cancel_callbacks_.clear();

  const vector<shared_ptr<Task>> child_tasks(child_tasks_);

  TryDoneTransition(&lock);

  if (lock.owns_lock()) {
    lock.unlock();
  }

  for (const auto& child_task : child_tasks) {
    child_task->Cancel();
  }

  return true;
}


void Task::AddHold() {
  lock_guard<mutex> lock(lock_);
  CHECK_NE(state_, DONE);
  ++holds_;
}


void Task::RemoveHold() {
  unique_lock<mutex> lock(lock_);

  CHECK_GT(holds_, 0);
  CHECK_NE(state_, DONE);
  --holds_;

  TryDoneTransition(&lock);
}


bool Task::IsActive() const {
  lock_guard<mutex> lock(lock_);
  return state_ == ACTIVE;
}


bool Task::IsDone() const {
  lock_guard<mutex> lock(lock_);
  return state_ == DONE;
}


bool Task::CancelRequested() const {
  lock_guard<mutex> lock(lock_);
  return cancelled_;
}


void Task::WhenCancelled(const std::function<void()>& cancel_cb) {
  unique_lock<mutex> lock(lock_);

  if (state_ != ACTIVE) {
    return;
  }

  if (!cancelled_) {
    cancel_callbacks_.emplace_back(cancel_cb);
  } else {
    ++holds_;

    lock.unlock();
    executor_->Add(bind(&Task::RunCancelCallback, this, cancel_cb));
  }
}


Task* Task::AddChildWithExecutor(const function<void(Task*)>& done_callback,
                                 Executor* executor) {
  const shared_ptr<Task> child_task(make_shared<Task>(
      bind(&Task::RunChildDoneCallback, this, done_callback, _1),
      CHECK_NOTNULL(executor)));
  bool cancel;

  {
    lock_guard<mutex> lock(lock_);
    CHECK_NE(state_, DONE);

    child_tasks_.emplace_back(child_task);
    ++holds_;

    cancel = state_ != ACTIVE || cancelled_;
  }

  if (cancel) {
    child_task->Cancel();
  }

  return child_task.get();
}


void Task::CleanupWhenDone(const function<void()>& cleanup_cb) {
  lock_guard<mutex> lock(lock_);
  CHECK_NE(state_, DONE);

  cleanup_callbacks_.emplace_back(cleanup_cb);
}

void Task::TryDoneTransition(unique_lock<mutex>* lock) {
  CHECK(lock->owns_lock());
  CHECK_NE(state_, DONE);

  if (state_ != PREPARED || holds_ > 0) {
    return;
  }

  state_ = DONE;

  lock->unlock();

  executor_->Add(bind(&Task::RunCleanupAndDoneCallbacks, this));
}


void Task::RunCancelCallback(const std::function<void()>& cb) {
  cb();
  RemoveHold();
}


void Task::RunCleanupAndDoneCallbacks() {
  vector<function<void()>> cleanup_callbacks;

  {
    lock_guard<mutex> lock(lock_);
    cleanup_callbacks_.swap(cleanup_callbacks);
  }

  for (const auto& cb : cleanup_callbacks) {
    cb();
  }

  done_callback_(this);
}


void Task::RunChildDoneCallback(const function<void(Task*)>& done_callback,
                                Task* child_task) {
  done_callback(child_task);

  unique_lock<mutex> lock(lock_);
  vector<shared_ptr<Task>>::iterator it;
  for (it = child_tasks_.begin(); it != child_tasks_.end(); ++it) {
    if (it->get() == child_task) {
      break;
    }
  }

  CHECK(it != child_tasks_.end());
  CHECK_GT(holds_, 0);
  CHECK_NE(state_, DONE);

  child_tasks_.erase(it);
  --holds_;

  TryDoneTransition(&lock);
}


}  // namespace mpr_pgw
