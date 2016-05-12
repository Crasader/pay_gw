#include <iostream>
#include <memory>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "server/server.h"
#include "server/pgw_handler.h"
#include "base/libevent_wrapper.h"
#include "base/status.h"
#include "base/thread_pool.h"


using namespace mpr_pgw;

void Init(int* argc, char** argv[]) {
  google::ParseCommandLineFlags(argc, argv, true);
  google::InitGoogleLogging(*argv[0]);
  google::InstallFailureSignalHandler();

  evthread_use_pthreads();
  evhtp_ssl_use_threads();

  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();
  SSL_library_init();

}

int main(int argc, char**argv) {

  Init(&argc, &argv);  

  Server::StaticInit();

  std::shared_ptr<libevent::Base> event_base(
		  std::make_shared<libevent::Base>());
  ThreadPool internal_pool(8);
  UrlFetcher url_fetcher(event_base.get(), &internal_pool);
  ThreadPool http_pool(4);
  Server server(event_base, &internal_pool, &http_pool, &url_fetcher);
  server.Initialise();

  PgwHandler handler(&internal_pool, event_base.get());
  handler.Add(server.http_server());

  LOG(INFO) << "Server Running: ";
  server.Run();

  return 0;
}


#if 0
#include "base/thread_pool.h"
#include "base/libevent_wrapper.h"
#include "base/sync_task.h"
#include "net/url_fetcher.h"

using namespace mpr_pgw;

 class LocalhostResolver : public libevent::Base::Resolver {
   public:
    std::string Resolve(const std::string& name) override {
      (void)name;
      return "127.0.0.1";
    }
  };

class UrlFetcherTest {
   public:
    UrlFetcherTest()
        : base_(std::make_shared<libevent::Base>(
              std::unique_ptr<libevent::Base::Resolver>(new LocalhostResolver))),
          event_pump_(base_),
          pool_(1) {
//      FLAGS_trusted_root_certs = FLAGS_cert_dir + "/ca-cert.pem";
      fetcher_.reset(new UrlFetcher(base_.get(), &pool_));
   }
   std::shared_ptr<libevent::Base> base_;
   std::shared_ptr<UrlFetcher> fetcher_;
   libevent::EventPumpThread event_pump_;
   ThreadPool pool_;
};
  

int main() { 
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();
  SSL_library_init();

  UrlFetcherTest fetcher;
  UrlFetcher::Request req(URL("http://www.baidu.com"));
  UrlFetcher::Response resp;
  
  SyncTask task(&fetcher.pool_);
  fetcher.fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  std::cout << "task status: " << task.status().ToString() << std::endl;
  std::cout << "status code: " << resp.status_code << std::endl;
  std::cout << "resp body: " << resp.body << std::endl;
  return 0; 
}
#endif
