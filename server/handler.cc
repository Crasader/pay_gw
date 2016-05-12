#include "server/handler.h"

#include <functional>
#include <glog/logging.h>

using std::placeholders::_1;
using std::bind;

namespace mpr_pgw {

void StatsHandlerInterceptor(const std::string& path,
		         const libevent::HttpServer::HandlerCallback& cb,
			 evhttp_request* req) {
  //do something;
  cb(req);
}

HttpHandler::HttpHandler(ThreadPool* pool, libevent::Base* event_base)
  : pool_(CHECK_NOTNULL(pool)),
    event_base_(CHECK_NOTNULL(event_base)) {
}

HttpHandler::~HttpHandler() {
}

void HttpHandler::ProxyInterceptor(
    const libevent::HttpServer::HandlerCallback& local_handler,
    evhttp_request* request) {
  //TODO:
  local_handler(request);
} 

void HttpHandler::AddProxyWrappedHandler(
    libevent::HttpServer* server,
    const std::string& path,
    const libevent::HttpServer::HandlerCallback& local_handler) {
  
  const libevent::HttpServer::HandlerCallback stats_handler(
      bind(&StatsHandlerInterceptor, path, local_handler, _1));
  server->AddHandler(path,
		     bind(&HttpHandler::ProxyInterceptor, 
			       this,
			       stats_handler,
			       _1));
}

void HttpHandler::Add(libevent::HttpServer* server) {
  CHECK_NOTNULL(server);

  AddProxyWrappedHandler(server, 
		         "/pgw/v1/ali/orderinfo",
		         bind(&HttpHandler::CreateAliOrderInfo, 
				   this, _1));
  AddHandlers(server);
}

// Handles
void HttpHandler::CreateAliOrderInfo(evhttp_request* req) const {
  //LOG(INFO) << "req.body: " << req->body;
  LOG(INFO) << "CreateAliOrderInfo";
}

} // namespace mpr_pgw
