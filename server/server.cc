#include "server/server.h"
#include <chrono>
#include <csignal>
#include <functional>

#include <glog/logging.h>

#include "base/thread_pool.h"

namespace mpr_pgw {

// static
void Server::StaticInit() {
}

Server::Server(const std::shared_ptr<libevent::Base>& event_base,
               ThreadPool* internal_pool,
	       ThreadPool* http_pool,
	       UrlFetcher* url_fetcher)
  : event_base_(event_base),
    event_pump_(new libevent::EventPumpThread(event_base_)),
    http_server_(*event_base_),
    url_fetcher_(CHECK_NOTNULL(url_fetcher)),
    internal_pool_(CHECK_NOTNULL(internal_pool)),
    server_task_(internal_pool_),
    http_pool_(CHECK_NOTNULL(http_pool)) {
  //TODO
  http_server_.Bind(nullptr, 8089);
}

Server::~Server() {
  server_task_.Cancel();
  server_task_.Wait();
}

libevent::HttpServer* Server::http_server() {
  return &http_server_;
}

void Server::Initialise() {
  //TODO:
}

void Server::Run() {
  event_pump_.reset();
  event_base_->Dispatch();
}

} // namespace mpr_pgw
