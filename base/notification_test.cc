#include <gtest/gtest.h>

#include "base/notification.h"

using std::chrono::milliseconds;

namespace mpr_pgw {


TEST(NotificationTest, BasicTests) {
  Notification notifier;

  ASSERT_FALSE(notifier.HasBeenNotified());
  EXPECT_FALSE(notifier.WaitForNotificationWithTimeout(milliseconds(0)));
  EXPECT_FALSE(notifier.WaitForNotificationWithTimeout(milliseconds(10)));
  notifier.Notify();
  notifier.WaitForNotification();
  EXPECT_TRUE(notifier.WaitForNotificationWithTimeout(milliseconds(0)));
  EXPECT_TRUE(notifier.WaitForNotificationWithTimeout(milliseconds(10)));
  ASSERT_TRUE(notifier.HasBeenNotified());
}


TEST(NotificationDeathTest, NotifyOnce) {
  Notification notifier;

  ASSERT_FALSE(notifier.HasBeenNotified());
  notifier.Notify();
  ASSERT_TRUE(notifier.HasBeenNotified());
  EXPECT_DEATH(notifier.Notify(), "Check failed: !notified_");
}


}  // namespace


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
