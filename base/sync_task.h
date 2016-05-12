#ifndef CERT_TRANS_UTIL_SYNC_TASK_H_
#define CERT_TRANS_UTIL_SYNC_TASK_H_

#include "base/macros.h"
#include "base/notification.h"
#include "base/task.h"

namespace mpr_pgw {

class SyncTask {
 public:
  SyncTask(Executor* executor);

  ~SyncTask();

  Task* task() {
    return &task_;
  }

  bool IsDone() const;
  Status status() const {
    return task_.status();
  }
  void Wait() const;
  void Cancel();

 private:
  Notification notifier_;
  Task task_;

  DISALLOW_COPY_AND_ASSIGN(SyncTask);
};


}  // namespace util

#endif  // CERT_TRANS_UTIL_SYNC_TASK_H_
