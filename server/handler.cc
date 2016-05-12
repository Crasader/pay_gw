#include "server/handler.h"

#include <glog/logging.h>

namespace mpr_pgw {

HttpHandler::HttpHandler(ThreadPool* pool, libevent::Base* event_base)
  : pool_(CHECK_NOTNULL(pool)),
    event_base_(CHECK_NOTNULL(event_base)) {
}


} // namespace mpr_pgw
