#ifndef MPR_PGW_BASE_TEMPLATE_UTIL_H_
#define MPR_PGW_BASE_TEMPLATE_UTIL_H_
#include <ctype.h>
#include <algorithm>
#include <string>

namespace mpr_pgw {

template <class T>
struct ci_less;

template <>
struct ci_less<int> {
  bool operator()(int lhs, int rhs) const {
    return tolower(lhs) < tolower(rhs);
  }
};

template <>
struct ci_less<std::string> {
  bool operator()(const std::string& lhs, const std::string& rhs) const {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end(), ci_less<int>());
  }
};

} // namespace mpr_pgw
#endif // MPR_PGW_BASE_TEMPLATE_UTIL_H_
