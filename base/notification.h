#ifndef MPR_PGW_BASE_NOTIFICATION_H_
#define MPR_PGW_BASE_NOTIFICATION_H_
#include <chrono>
#include <condition_variable>
#include <mutex>

#include "base/macros.h"

namespace mpr_pgw {

class Notification {
 public:
  Notification() : notified_(false) {
  }

  void Notify();
  bool HasBeenNotified() const;
  void WaitForNotification() const;
  bool WaitForNotificationWithTimeout(const std::chrono::milliseconds& timeout) const;

 private:
  mutable std::mutex lock_;
  mutable std::condition_variable cv_;
  bool notified_;

  DISALLOW_COPY_AND_ASSIGN(Notification);
};

} // namespace mpr_pgw
#endif // MPR_PGW_BASE_NOTIFICATION_H_

