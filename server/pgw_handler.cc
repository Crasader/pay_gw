#include "server/pgw_handler.h"

#include "base/status.h"
#include "base/thread_pool.h"

#include <functional>

namespace mpr_pgw {

PgwHandler::PgwHandler(ThreadPool* pool, libevent::Base* event_base)
  : HttpHandler(pool, event_base) {
}

void PgwHandler::AddHandlers(libevent::HttpServer* server) {
  //
}

} // namespace mpr_pgw
