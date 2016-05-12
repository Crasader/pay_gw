#ifndef MPR_PGW_BASE_EXECUTOR_H_
#define MPR_PGW_BASE_EXECUTOR_H_

#include <chrono>
#include <functional>

#include "base/macros.h"

namespace mpr_pgw {
class Task;

class Executor {
 public:
  virtual ~Executor() = default;
  
  virtual void Add(const std::function<void()>& closure) = 0;
  virtual void Delay(const std::chrono::duration<double>& delay,
                     Task* task) = 0;

 protected:
  Executor() = default;

 private:
  DISALLOW_COPY_AND_ASSIGN(Executor);
};

} // mpr_pgw
#endif // MPR_PGW_BASE_EXECUTOR_H_
