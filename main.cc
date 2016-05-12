#include <iostream>
#include <memory>

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
