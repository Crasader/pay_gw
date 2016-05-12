#ifndef MPR_PGW_SERVER_HANDLER_H_
#define MPR_PGW_SERVER_HANDLER_H_

#include "base/macros.h"
#include "base/libevent_wrapper.h"
#include "base/thread_pool.h"

namespace mpr_pgw {

#if 0
class Handle {
 public:
  virtual ~Handle();
  virtual void handle(libevent::Base *event_base);
};
#endif

class HttpHandler {
 public:
  HttpHandler(ThreadPool* pool, libevent::Base* event_base);  
  virtual ~HttpHandler();
  void Add(libevent::HttpServer* server);

 protected:
  virtual void AddHandlers(libevent::HttpServer* server) = 0;

  void ProxyInterceptor(
      const libevent::HttpServer::HandlerCallback& local,
      evhttp_request* request);

  void AddProxyWrappedHandler(
      libevent::HttpServer* server,
      const std::string& path,
      const libevent::HttpServer::HandlerCallback& local_handler);

  //void GetAliOrderInfo(evhtp_request* req) const;
  void CreateAliOrderInfo(evhttp_request* req) const;

  ThreadPool* const pool_;
  libevent::Base* const event_base_;
  DISALLOW_COPY_AND_ASSIGN(HttpHandler);  
};

} // namespace mpr_pgw
#endif // MPR_PGW_SERVER_HANDLER_H_
