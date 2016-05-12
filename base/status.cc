#include <sstream>
#include "base/status.h"

namespace mpr_pgw {

namespace {

const Status& CreateOkStatus() {
  static const Status status;
  return status;
}

const Status& CreateUnknownStatus() {
  static const Status status(error::UNKNOWN, "");
  return status;
}

const Status& CreateCancelledStatus() {
  static const Status status(error::CANCELLED, "");
  return status;
}

} // namespace

const Status& Status::OK = CreateOkStatus();
const Status& Status::UNKNOWN = CreateUnknownStatus();
const Status& Status::CANCELLED = CreateCancelledStatus();

Status::Status() 
  : code_(error::OK), 
    message_("") {
}

Status::Status(error::Code error, const std::string& error_message)
    : code_(error), 
      message_(error_message) {
  if (code_ == error::OK) {
    message_.clear();
  }
}

Status::Status(const Status& other)
    : code_(other.code_), 
      message_(other.message_) {
}

Status& Status::operator=(const Status& other) {
  code_ = other.code_;
  message_ = other.message_;
  return *this;
}

std::string Status::ToString() const {
  if (code_ == error::OK) {
    return "OK";
  }

  std::ostringstream oss;
  oss << code_ << ": " << message_;
  return oss.str();
}

std::string ErrorCodeString(error::Code error) {
  switch (error) {
    case error::OK:                 return "OK";
    case error::CANCELLED:          return "CANCELLED";
    case error::UNKNOWN:            return "UNKNOWN";
    case error::INVALID_ARGUMENT:   return "INVALID_ARGUMENT";
    case error::DEADLINE_EXCEEDED:  return "DEADLINE_EXCEEDED";
    case error::NOT_FOUND:          return "NOT_FOUND";
    case error::ALREADY_EXISTS:     return "ALREADY_EXISTS";
    case error::PERMISSION_DENIED:  return "PERMISSION_DENIED";
    case error::RESOURCE_EXHAUSTED: return "RESOURCE_EXHAUSTED";
    case error::FAILED_PRECONDITION: return "FAILED_PRECONDITION";
    case error::ABORTED:            return "ABORTED";
    case error::OUT_OF_RANGE:       return "OUT_OF_RANGE";
    case error::UNIMPLEMENTED:      return "UNIMPLEMENTED";
    case error::INTERNAL:           return "INTERNAL";
    case error::UNAVAILABLE:        return "UNAVAILABLE";
    case error::DATA_LOSS:          return "DATA_LOSS";
  }
  return std::to_string(error);
} 

extern std::ostream& operator<<(std::ostream& os, error::Code code) {
  os << ErrorCodeString(code);
  return os;
} 

extern std::ostream& operator<<(std::ostream& os, const Status& other) {
  os << other.ToString();
  return os;
}

} // namespace mpr_pgw
