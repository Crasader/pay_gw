#ifndef UTIL_STATUSOR_H__
#define UTIL_STATUSOR_H__


#include <glog/logging.h>
#include "base/status.h"

namespace mpr_pgw {

// A StatusOr holds a Status (in the case of an error), or a value T.
template <typename T>
class StatusOr {
 public:
  // Has status UNKNOWN.
  inline StatusOr();

  // Builds from a non-OK status. Crashes if an OK status is specified.
  inline StatusOr(const Status& status);  // NOLINT

  // Builds from the specified value.
  inline StatusOr(const T& value);  // NOLINT

  // Copy constructor.
  inline StatusOr(const StatusOr& other);

  // Conversion copy constructor, T must be copy constructible from U.
  template <typename U>
  inline StatusOr(const StatusOr<U>& other);

  // Assignment operator.
  inline const StatusOr& operator=(const StatusOr& other);

  // Conversion assignment operator, T must be assignable from U
  template <typename U>
  inline const StatusOr& operator=(const StatusOr<U>& other);

  // Accessors.
  inline const Status& status() const {
    return status_;
  }

  // Shorthand for status().ok().
  inline bool ok() const {
    return status_.ok();
  }

  // Returns value or crashes if ok() is false.
  inline const T& ValueOrDie() const {
    CHECK(ok()) << "Attempting to fetch value of non-OK StatusOr";
    return value_;
  }

  template <typename U>
  friend class StatusOr;

 private:
  Status status_;
  T value_;
};

// Implementation.

template <typename T>
inline StatusOr<T>::StatusOr() : status_(error::UNKNOWN, "") {
}

template <typename T>
inline StatusOr<T>::StatusOr(const Status& status) : status_(status) {
  CHECK(!status.ok()) << "Status::OK is not a valid argument to StatusOr";
}

template <typename T>
inline StatusOr<T>::StatusOr(const T& value) : value_(value) {
}

template <typename T>
inline StatusOr<T>::StatusOr(const StatusOr& other)
    : status_(other.status_), value_(other.value_) {
}

template <typename T>
template <typename U>
inline StatusOr<T>::StatusOr(const StatusOr<U>& other)
    : status_(other.status_), value_(other.value_) {
}

template <typename T>
inline const StatusOr<T>& StatusOr<T>::operator=(const StatusOr& other) {
  status_ = other.status_;
  if (status_.ok()) {
    value_ = other.value_;
  }
  return *this;
}

template <typename T>
template <typename U>
inline const StatusOr<T>& StatusOr<T>::operator=(const StatusOr<U>& other) {
  status_ = other.status_;
  if (status_.ok()) {
    value_ = other.value_;
  }
  return *this;
}

}  // namespace util

#endif  // UTIL_STATUSOR_H__
