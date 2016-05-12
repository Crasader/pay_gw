#ifndef MPR_PGW_SERVER_SERVER_H_
#define MPR_PGW_SERVER_SERVER_H_
#include <stdint.h>
#include <thread>
#include <string>
#include <thread>
#include <memory>

#include "base/macros.h"
#include "base/libevent_wrapper.h"
#include "base/sync_task.h"
#include "net/url_fetcher.h"

namespace mpr_pgw {

class ThreadPool;
class UrlFetcher;

class Server {
 public:
  static void StaticInit();
  Server(const std::shared_ptr<libevent::Base>& event_base,
         ThreadPool* internal_pool,
	 ThreadPool* http_pool,
	 UrlFetcher* url_fetcher);
  ~Server();

  libevent::HttpServer* http_server();

  //void Initialise(bool is_mirror);
  void Initialise();
  void Run();
 private:
  const std::shared_ptr<libevent::Base> event_base_;
  std::unique_ptr<libevent::EventPumpThread> event_pump_;
  libevent::HttpServer http_server_;
  UrlFetcher* const url_fetcher_;
  ThreadPool* const internal_pool_;
  SyncTask server_task_;
  ThreadPool* const http_pool_;

  DISALLOW_COPY_AND_ASSIGN(Server);
};

} // namespace mpr_pgw
#endif // MPR_PGW_SERVER_SERVER_H_
