#include "base/thread_pool.h"
#include "base/task.h"

#include <glog/logging.h>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::condition_variable;
using std::function;
using std::get;
using std::lock_guard;
using std::mutex;
using std::priority_queue;
using std::thread;
using std::tuple;
using std::unique_lock;
using std::vector;

namespace mpr_pgw {

namespace {

typedef tuple<steady_clock::time_point, function<void()>, Task*>
    QueueEntry;


struct QueueOrdering {
  bool operator()(const QueueEntry& lhs, const QueueEntry& rhs) const {
    return get<0>(lhs) > get<0>(rhs);
  }
};


}  // namespace


class ThreadPool::Impl {
 public:
  ~Impl();

  void Worker();

  vector<thread> threads_;

  mutex queue_lock_;
  condition_variable queue_cond_var_;
  priority_queue<QueueEntry, vector<QueueEntry>, QueueOrdering> queue_;
};


ThreadPool::Impl::~Impl() {
  {
    lock_guard<mutex> lock(queue_lock_);
    for (int i = threads_.size(); i > 0; --i)
      queue_.emplace(
          make_tuple(steady_clock::time_point(), function<void()>(), nullptr));
  }
  queue_cond_var_.notify_all();

  for (auto& thread : threads_) {
    thread.join();
  }

  CHECK(queue_.empty());
}


void ThreadPool::Impl::Worker() {
  while (true) {
    QueueEntry entry;

    {
      unique_lock<mutex> lock(queue_lock_);
      while (queue_.empty() || get<0>(queue_.top()) > steady_clock::now()) {
        if (queue_.empty()) {
          queue_cond_var_.wait(lock);
        } else {
          const steady_clock::duration duration(get<0>(queue_.top()) -
                                                steady_clock::now());
          queue_cond_var_.wait_for(lock, duration);
        }
      }

      entry = queue_.top();
      queue_.pop();

      if (!get<1>(entry)) {
        VLOG(1) << "Cancelling delayed tasks...";
        vector<Task*> to_be_cancelled;
        while (!queue_.empty() && get<2>(queue_.top())) {
          to_be_cancelled.push_back(CHECK_NOTNULL(get<2>(queue_.top())));
          queue_.pop();
        }

        lock.unlock();

        for (const auto& t : to_be_cancelled) {
          t->Return(Status::CANCELLED);
        }

        VLOG(1) << "Cancelled " << to_be_cancelled.size() << " delayed tasks.";
        return;
      }
    }

    get<1>(entry)();
  }
}


ThreadPool::ThreadPool()
    : ThreadPool(thread::hardware_concurrency() > 0
                     ? thread::hardware_concurrency()
                     : 1) {
}


ThreadPool::ThreadPool(size_t num_threads) : impl_(new Impl) {
  CHECK_GT(num_threads, static_cast<size_t>(0));
  LOG(INFO) << "ThreadPool starting with " << num_threads << " threads";
  for (int i = 0; i < static_cast<int64_t>(num_threads); ++i)
    impl_->threads_.emplace_back(thread(&Impl::Worker, impl_.get()));
}


ThreadPool::~ThreadPool() {
  // Need to have this method defined where the definition of
  // ThreadPool::Impl is visible.
}


void ThreadPool::Add(const function<void()>& closure) {
  if (!closure) {
    return;
  }

  {
    lock_guard<mutex> lock(impl_->queue_lock_);
    impl_->queue_.emplace(make_tuple(steady_clock::now(), closure, nullptr));
  }
  impl_->queue_cond_var_.notify_one();
}


void ThreadPool::Delay(const duration<double>& delay, Task* task) {
  CHECK_NOTNULL(task);
  {
    lock_guard<mutex> lock(impl_->queue_lock_);
    impl_->queue_.emplace(make_tuple(
        steady_clock::now() + duration_cast<std::chrono::microseconds>(delay),
        [task]() { task->Return(); }, task));
  }
  impl_->queue_cond_var_.notify_one();
}


}  // namespace mpr_pgw
