#include <arpa/inet.h>
#include <arpa/nameser.h> /* DNS HEADER struct */
#include <fcntl.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <csignal>
#include <netdb.h>
#include <netdb.h>
#include <netinet/in.h> /* inet_ functions / structs */
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "net/connection_pool.h"
#include "net/url_fetcher.h"
#include "base/libevent_wrapper.h"
#include "base/status_test_util.h"
#include "base/sync_task.h"
#include "base/thread_pool.h"

DECLARE_int32(connection_read_timeout_seconds);
DECLARE_int32(connection_write_timeout_seconds);
DECLARE_string(trusted_root_certs);

namespace mpr_pgw {

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::unique_ptr;

DEFINE_string(cert_dir, "test/testdata/urlfetcher_test_certs",
              "Directory containing the test certs.");


const uint16_t kLocalHostPort = 4433;
const uint16_t kNonLocalHostPort = 4434;
const uint16_t kStarExampleComPort = 4435;
const uint16_t kBinkyExampleComPort = 4436;
const uint16_t kExampleComPort = 4437;
const uint16_t k127_0_0_1Port = 4438;
const uint16_t kHangPort = 4439;


namespace {


class LocalhostResolver : public libevent::Base::Resolver {
 public:
  string Resolve(const std::string& name) override {
    return "127.0.0.1";
  }
};


pid_t RunOpenSSLServer(uint16_t port, const std::string& cert_file,
                       const std::string& key_file,
                       const std::string& mode = "-www") {
#ifdef HAVE_WORKING_VFORK
  pid_t pid(vfork());
#else
  pid_t pid(fork());
#endif

  if (pid == -1) {
    LOG(INFO) << "fork() failed: " << pid;
  } else if (pid == 0) {
    const string port_str(to_string(port));
    const string cert_str(FLAGS_cert_dir + "/" + cert_file);
    const string key_str(FLAGS_cert_dir + "/" + key_file);
    const char* argv[]{"openssl",    "s_server",
                       "-accept",    port_str.c_str(),
                       "-cert",      cert_str.c_str(),
                       "-key",       key_str.c_str(),
                       mode.c_str(), 0L};
    execvp(argv[0], const_cast<char**>(argv));
  }
  return pid;
}


}  // namespace


class UrlFetcherTest : public ::testing::Test {
 public:
  UrlFetcherTest()
      : base_(make_shared<libevent::Base>(
            unique_ptr<libevent::Base::Resolver>(new LocalhostResolver))),
        event_pump_(base_),
        pool_() {
    FLAGS_trusted_root_certs = FLAGS_cert_dir + "/ca-cert.pem";
    fetcher_.reset(new UrlFetcher(base_.get(), &pool_));
  }

 protected:
  shared_ptr<libevent::Base> base_;
  shared_ptr<UrlFetcher> fetcher_;
  libevent::EventPumpThread event_pump_;
  ThreadPool pool_;
};


TEST_F(UrlFetcherTest, TestCertMatchesHost) {
  UrlFetcher::Request req(
      URL("https://localhost:" + to_string(kLocalHostPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_OK(task.status());
  EXPECT_EQ(200, resp.status_code);
}


TEST_F(UrlFetcherTest, TestCertDoesNotMatchHost) {
  UrlFetcher::Request req(
      URL("https://localhost:" + to_string(kNonLocalHostPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestNotListening) {
  UrlFetcher::Request req(URL("https://localhost:63544"));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kUnknownErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestStarMatchesSubdomain) {
  UrlFetcher::Request req(
      URL("https://donkey.example.com:" + to_string(kStarExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_OK(task.status());
  EXPECT_EQ(200, resp.status_code);
}


TEST_F(UrlFetcherTest, TestStarDoesNotMatcheIncorrectParentDomain) {
  UrlFetcher::Request req(
      URL("https://donkey.9600.org:" + to_string(kStarExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestSubdomainMatches) {
  UrlFetcher::Request req(
      URL("https://binky.example.com:" + to_string(kBinkyExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_OK(task.status());
  EXPECT_EQ(200, resp.status_code);
}


TEST_F(UrlFetcherTest, TestSubdomainDoesNotMatchIncorrectParentDomain) {
  UrlFetcher::Request req(
      URL("https://binky.9600.org:" + to_string(kBinkyExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestSubstringSubjectDoesNotMatch) {
  UrlFetcher::Request req(
      URL("https://superexample.com:" + to_string(kExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestSuperstringSubjectDoesNotMatch) {
  UrlFetcher::Request req(
      URL("https://xample.com:" + to_string(kExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestSubstringHostDoesNotMatch) {
  UrlFetcher::Request req(URL("https://exampl:" + to_string(kExampleComPort)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestIpMatches) {
  UrlFetcher::Request req(
      URL("https://127.0.0.1:" + to_string(k127_0_0_1Port)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_OK(task.status());
  EXPECT_EQ(200, resp.status_code);
}


TEST_F(UrlFetcherTest, TestWrongIpDoesNotMatch) {
  UrlFetcher::Request req(URL("https://1.2.3.4:" + to_string(k127_0_0_1Port)));
  UrlFetcher::Response resp;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();
  EXPECT_THAT(task.status(), testing::StatusIs(error::UNAVAILABLE));
  EXPECT_EQ(kSSLErrorStatus, resp.status_code);
}


TEST_F(UrlFetcherTest, TestTimeout) {
  UrlFetcher::Request req(URL("http://localhost:" + to_string(kHangPort)));
  UrlFetcher::Response resp;

  FLAGS_connection_read_timeout_seconds = 1;
  FLAGS_connection_write_timeout_seconds = 1;

  SyncTask task(&pool_);
  fetcher_->Fetch(req, &resp, task.task());
  task.Wait();

  EXPECT_THAT(task.status(), testing::StatusIs(error::DEADLINE_EXCEEDED));
  EXPECT_EQ(kTimeout, resp.status_code);
}


}  // namespace cert_trans


namespace {


pid_t localhost_pid(0);
pid_t nonlocalhost_pid(0);
pid_t star_example_com_pid(0);
pid_t binky_example_com_pid(0);
pid_t example_com_pid(0);
pid_t ip_address_pid(0);


void KillAllOpenSSLServers() {
  kill(localhost_pid, SIGTERM);
  kill(nonlocalhost_pid, SIGTERM);
  kill(star_example_com_pid, SIGTERM);
  kill(binky_example_com_pid, SIGTERM);
  kill(example_com_pid, SIGTERM);
  kill(ip_address_pid, SIGTERM);
  waitpid(localhost_pid, nullptr, 0);
  waitpid(nonlocalhost_pid, nullptr, 0);
  waitpid(star_example_com_pid, nullptr, 0);
  waitpid(binky_example_com_pid, nullptr, 0);
  waitpid(example_com_pid, nullptr, 0);
  waitpid(ip_address_pid, nullptr, 0);
}


}  // namespace


int main(int argc, char** argv) {
  //mpr_pgw::test::InitTesting(argv[0], &argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();
  SSL_library_init();

  signal(SIGPIPE, SIG_IGN);

  int hang_fd(socket(AF_INET, SOCK_STREAM, 0));
  CHECK_NE(-1, hang_fd);
  CHECK_NE(-1, fcntl(hang_fd, F_SETFL, O_NONBLOCK));
  struct sockaddr_in hang_addr;
  bzero((char*)&hang_addr, sizeof(hang_addr));
  hang_addr.sin_family = AF_INET;
// Prefer to use INADDR_LOOPBACK if available as it avoids the firewall
// triggering on some platforms if we bind a non-local address.
#ifdef HAVE_INADDR_LOOPBACK
  hang_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#else
  hang_addr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif
  hang_addr.sin_port = htons(mpr_pgw::kHangPort);
  CHECK_EQ(0, bind(hang_fd, reinterpret_cast<struct sockaddr*>(&hang_addr),
                   sizeof(hang_addr)))
      << strerror(errno);
  CHECK_EQ(0, listen(hang_fd, 10));
  struct sockaddr_in other_addr;
  socklen_t other_size;
  accept(hang_fd, reinterpret_cast<struct sockaddr*>(&other_addr),
         &other_size);

  localhost_pid =
      mpr_pgw::RunOpenSSLServer(mpr_pgw::kLocalHostPort,
                                   "localhost-cert.pem", "localhost-key.pem");
  nonlocalhost_pid =
      mpr_pgw::RunOpenSSLServer(mpr_pgw::kNonLocalHostPort,
                                   "not-localhost-cert.pem",
                                   "not-localhost-key.pem");
  star_example_com_pid =
      mpr_pgw::RunOpenSSLServer(mpr_pgw::kStarExampleComPort,
                                   "star_example_com-cert.pem",
                                   "star_example_com-key.pem");
  binky_example_com_pid =
      mpr_pgw::RunOpenSSLServer(mpr_pgw::kBinkyExampleComPort,
                                   "binky_example_com-cert.pem",
                                   "binky_example_com-key.pem");
  example_com_pid = mpr_pgw::RunOpenSSLServer(mpr_pgw::kExampleComPort,
                                                 "example_com-cert.pem",
                                                 "example_com-key.pem");
  ip_address_pid =
      mpr_pgw::RunOpenSSLServer(mpr_pgw::k127_0_0_1Port,
                                   "127_0_0_1-cert.pem", "127_0_0_1-key.pem");

  sleep(1);

  const int ret(RUN_ALL_TESTS());
  KillAllOpenSSLServers();
  close(hang_fd);
  return ret;
}
