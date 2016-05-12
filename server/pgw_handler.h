#ifndef MPR_PGW_SERVER_PGW_HANDLER_H_
#define MPR_PGW_SERVER_PGW_HANDLER_H_
#include "server/handler.h"

namespace mpr_pgw {

class PgwHandler : public HttpHandler {
 public:
  PgwHandler(ThreadPool* pool, libevent::Base* event_base);
  ~PgwHandler() = default;

 protected:
  void AddHandlers(libevent::HttpServer* server) override;

  DISALLOW_COPY_AND_ASSIGN(PgwHandler);
};

} // namespace mpr_pgw
#endif // MPR_PGW_SERVER_PGW_HANDLER_H_
