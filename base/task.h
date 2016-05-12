#ifndef MPR_PGW_BASE_TASK_H_
#define MPR_PGW_BASE_TASK_H_

#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "base/macros.h"
#include "base/executor.h"
#include "base/status.h"

namespace mpr_pgw {

class Task {
 public:
  Task(const std::function<void(Task*)>& done_callback, Executor* executor);
  ~Task();

  Executor* executor() const;
  void Cancel();
  Status status() const;
  bool Return(const Status& status=Status::OK);

  void AddHold();
  void RemoveHold();
  bool IsActive() const;
  bool IsDone() const;
  bool CancelRequested() const;
  void WhenCancelled(const std::function<void()>& cancel_cb);

  Task* AddChild(const std::function<void(Task*)>& done_callback) {
    return AddChildWithExecutor(done_callback, executor_);
  }

  Task* AddChildWithExecutor(const std::function<void(Task*)>& done_callback,
                             Executor* executor);
  void CleanupWhenDone(const std::function<void()>& cleanup_cb);
  template<typename T>
  void DeleteWhenDone(T* obj) {
    CleanupWhenDone(std::bind(std::default_delete<T>(), obj));
  }

 private:
  enum State {
    ACTIVE = 0,
    PREPARED = 1,
    DONE = 2, 
  };
  
  void TryDoneTransition(std::unique_lock<std::mutex>* lock);
  void RunCancelCallback(const std::function<void()>& cb);
  void RunCleanupAndDoneCallbacks();
  void RunChildDoneCallback(const std::function<void(Task*)>& done_callback,
                            Task* child_task);

  const std::function<void(Task*)> done_callback_;
  Executor* const executor_;

  mutable std::mutex lock_;
  State state_;
  Status status_;
  bool cancelled_;
  int holds_;
  std::vector<std::shared_ptr<Task>> child_tasks_;
  std::vector<std::function<void()>> cancel_callbacks_;
  std::vector<std::function<void()>> cleanup_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(Task);
};

class TaskHold {
 public:
  TaskHold(Task* task) : task_(task) {
    task_->AddHold();
  }

  ~TaskHold() {
    task_->RemoveHold();
  }

 private:
  Task* const task_;

  DISALLOW_COPY_AND_ASSIGN(TaskHold);
};

} // namespace mpr_pgw
#endif // MPR_PGW_BASE_TASK_H_
