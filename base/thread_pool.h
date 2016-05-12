#ifndef CERT_TRANS_UTIL_THREAD_POOL_H_
#define CERT_TRANS_UTIL_THREAD_POOL_H_

#include <chrono>
#include <functional>
#include <map>
#include <memory>

#include "base/macros.h"
#include "base/executor.h"

namespace mpr_pgw {


class ThreadPool : public Executor {
 public:
  ThreadPool();

  ThreadPool(size_t num_threads);

  ~ThreadPool();

  void Add(const std::function<void()>& closure) override;

  void Delay(const std::chrono::duration<double>& delay,
             Task* task) override;

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;

  DISALLOW_COPY_AND_ASSIGN(ThreadPool);
};


}  // namespace mpr_pgw 

#endif  // CERT_TRANS_UTIL_THREAD_POOL_H_
