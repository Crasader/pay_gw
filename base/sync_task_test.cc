#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "base/sync_task.h"
#include "base/thread_pool.h"

using std::bind;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

namespace mpr_pgw {


TEST(SyncTaskTest, StateChange) {
  ThreadPool pool;
  SyncTask s(&pool);
  EXPECT_FALSE(s.IsDone());

  Status status(error::INTERNAL, "my own private status");
  s.task()->Return(status);
  s.Wait();

  EXPECT_TRUE(s.IsDone());
  EXPECT_EQ(status, s.status());
}


void DelayReturn(Task* task, const Status& status) {
  sleep_for(milliseconds(100));
  task->Return(status);
}


TEST(SyncTaskTest, Wait) {
  ThreadPool pool;
  SyncTask s(&pool);
  EXPECT_FALSE(s.IsDone());

  Status status(error::INTERNAL, "my own private status");
  pool.Add(bind(DelayReturn, s.task(), status));
  s.Wait();

  EXPECT_TRUE(s.IsDone());
  EXPECT_EQ(status, s.status());
}


void CancelTask(Task* task) {
  task->Return(Status::CANCELLED);
}


TEST(SyncTaskTest, CancelBefore) {
  ThreadPool pool;
  SyncTask s(&pool);
  EXPECT_FALSE(s.IsDone());

  s.task()->WhenCancelled(bind(CancelTask, s.task()));
  s.Cancel();
  s.Wait();

  EXPECT_TRUE(s.IsDone());
  EXPECT_EQ(Status::CANCELLED, s.status());
}


TEST(SyncTaskTest, CancelAfter) {
  ThreadPool pool;
  SyncTask s(&pool);
  EXPECT_FALSE(s.IsDone());

  s.task()->WhenCancelled(bind(CancelTask, s.task()));

  Status status(error::INTERNAL, "my own private status");
  s.task()->Return(status);

  s.Cancel();
  s.Wait();

  EXPECT_TRUE(s.IsDone());
  EXPECT_EQ(status, s.status());
}


}  // namespace


int main(int argc, char** argv) {
  //cert_trans::test::InitTesting(argv[0], &argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
