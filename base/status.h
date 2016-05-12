#ifndef MPR_PGW_BASE_STATUS_H_
#define MPR_PGW_BASE_STATUS_H_
#include <string>

namespace mpr_pgw {

namespace error {

enum Code {
  OK = 0,
  CANCELLED = 1,
  UNKNOWN = 2,
  INVALID_ARGUMENT = 3,
  DEADLINE_EXCEEDED = 4,
  NOT_FOUND = 5,
  ALREADY_EXISTS = 6,
  PERMISSION_DENIED = 7,
  RESOURCE_EXHAUSTED = 8,
  FAILED_PRECONDITION = 9,
  ABORTED = 10,
  OUT_OF_RANGE = 11,
  UNIMPLEMENTED = 12,
  INTERNAL = 13,
  UNAVAILABLE = 14,
  DATA_LOSS = 15,
};
} // namespace error

class Status {
 public:
  Status();
  Status(error::Code error, const std::string& error_message);

  Status(const Status& other);
  Status& operator=(const Status& other);

  static const Status& OK;
  static const Status& CANCELLED;
  static const Status& UNKNOWN;

  bool ok() const {
    return code_ == error::OK;
  }
  int error_code() const {
    return code_;
  }
  error::Code CanonicalCode() const {
    return code_;
  }
  const std::string& error_message() const {
    return message_;
  }

  bool operator==(const Status& other) const;
  bool operator!=(const Status& other) const;

  void IgnoreError() const {
  }

  std::string ToString() const;

 private:
  error::Code code_;
  std::string message_;
};

inline bool Status::operator==(const Status& other) const {
  return (this->code_ == other.code_) &&
         (this->message_ == other.message_);
}

inline bool Status::operator!=(const Status& other) const {
  return !(*this == other);
}

extern std::string ErrorCodeString(error::Code error);
extern std::ostream& operator<<(std::ostream& os,
                                error::Code code);
extern std::ostream& operator<<(std::ostream& os,
                                const Status& other);

} // namespace mpr_pgw
#endif // MPR_PGW_BASE_STATUS_H_
