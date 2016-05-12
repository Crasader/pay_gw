#include "base/sync_task.h"

#include <glog/logging.h>

using std::bind;

namespace mpr_pgw {


SyncTask::SyncTask(Executor* executor)
    : task_(bind(&Notification::Notify, &notifier_), CHECK_NOTNULL(executor)) {
}


SyncTask::~SyncTask() {
  CHECK(IsDone());
}


bool SyncTask::IsDone() const {
  return notifier_.HasBeenNotified();
}


void SyncTask::Wait() const {
  notifier_.WaitForNotification();
}


void SyncTask::Cancel() {
  task_.Cancel();
}


}  // namespace mpr_pgw
