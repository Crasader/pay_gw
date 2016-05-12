#ifndef CERT_TRANS_UTIL_STATUS_TEST_UTIL_H_
#define CERT_TRANS_UTIL_STATUS_TEST_UTIL_H_

#include <gmock/gmock-matchers.h>

#include "base/status.h"
#include "base/statusor.h"
#include "base/sync_task.h"
#include "base/task.h"

namespace mpr_pgw {
namespace testing {


class StatusIsMatcher : public ::testing::MatcherInterface<Status> {
 public:
  StatusIsMatcher(const ::testing::Matcher<error::Code>& code_matcher,
                  const ::testing::Matcher<std::string>& message_matcher)
      : code_matcher_(code_matcher), message_matcher_(message_matcher) {
  }

  bool MatchAndExplain(
      Status status, ::testing::MatchResultListener* listener) const override {
    if (!code_matcher_.MatchAndExplain(status.CanonicalCode(), listener)) {
      return false;
    }

    if (!message_matcher_.MatchAndExplain(status.error_message(), listener)) {
      return false;
    }

    return true;
  }

  void DescribeTo(std::ostream* os) const override {
    *os << "util::Status(code ";
    code_matcher_.DescribeTo(os);
    *os << " and message ";
    message_matcher_.DescribeTo(os);
    *os << ")";
  }

 private:
  const ::testing::Matcher<error::Code> code_matcher_;
  const ::testing::Matcher<std::string> message_matcher_;
};


::testing::Matcher<Status> StatusIs(
    const ::testing::Matcher<error::Code>& code_matcher,
    const ::testing::Matcher<std::string>& message_matcher) {
  return ::testing::MakeMatcher(
      new StatusIsMatcher(code_matcher, message_matcher));
}


::testing::Matcher<Status> StatusIs(
    const ::testing::Matcher<error::Code>& code_matcher) {
  return ::testing::MakeMatcher(
      new StatusIsMatcher(code_matcher, ::testing::_));
}


inline Status ToStatus(const Status& status) {
  return status;
}


inline Status ToStatus(Task* task) {
  return task->status();
}


inline Status ToStatus(const SyncTask& task) {
  return task.status();
}


template <class T>
Status ToStatus(const StatusOr<T>& statusor) {
  return statusor.status();
}


#define EXPECT_OK(expr) \
  EXPECT_EQ(mpr_pgw::Status::OK, mpr_pgw::testing::ToStatus(expr))
#define ASSERT_OK(expr) \
  ASSERT_EQ(mpr_pgw::Status::OK, mpr_pgw::testing::ToStatus(expr))


}  // namespace testing
}  // namespace util

#endif  // CERT_TRANS_UTIL_STATUS_TEST_UTIL_H_
