#ifndef MPR_PGW_BASE_MACROS_H_
#define MPR_PGW_BASE_MACROS_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

#endif // MPR_PGW_BASE_MACROS_H_
