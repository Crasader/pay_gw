APP:=mpr_pgw

CXXFLAGS += -I./
CXXFLAGS += -I./src
CXXFLAGS += -I./third_party/libevhtp/ 
CXXFLAGS += -I./third_party/libevhtp/evthr/ -I./third_party/libevhtp/htparse/
CXXFLAGS += -std=c++11 -g -c -o

CXX:=g++

LIB_FILES := -L./third_party/libevhtp/ -levhtp -lssl -lcrypto -lglog -lgflags -llzma -ldl -lpthread -lresolv -levent_openssl -levent_pthreads -levent
LIB_TESTS :=$(LIB_FILES) -lgtest -lpthread

CPP_SOURCES := ./base/notification.cc \
	./base/status.cc \
	./base/task.cc \
	./base/thread_pool.cc \
	./base/sync_task.cc \
	./base/libevent_wrapper.cc \
	./base/openssl_util.cc \
	\
	./net/url.cc \
	./net/connection_pool.cc \
	./net/url_fetcher.cc \
	\
	./server/handler.cc \
	./server/pgw_handler.cc \
	./server/server.cc \

CPP_OBJECTS := $(CPP_SOURCES:.cc=.o)

TESTS := \
	notification_test \
	thread_pool_test \
	#task_test \
	sync_task_test \
	libevent_wrapper_test \
	url_fetcher_test \


all: $(APP) $(TESTS)

$(APP): main.o $(CPP_OBJECTS)
	$(CXX) -o $(APP) main.o $(CPP_OBJECTS) $(LIB_FILES)

.cc.o:
	$(CXX) $(CXXFLAGS) $@ $<

url_fetcher_test: ./net/url_fetcher_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./net/url_fetcher_test.o: ./net/url_fetcher_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

libevent_wrapper_test: ./base/libevent_wrapper_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./base/libevent_wrapper_test.o: ./base/libevent_wrapper_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

notification_test: ./base/notification_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./base/notification_test.o: ./base/notification_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

thread_pool_test: ./base/thread_pool_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./base/thread_pool_test.o: ./base/thread_pool_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

task_test: ./base/task_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./base/task_test.o: ./base/task_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

sync_task_test: ./base/sync_task_test.o
	$(CXX) -o $@ $^ $(CPP_OBJECTS) $(LIB_TESTS)
./base/sync_task_test.o: ./base/sync_task_test.cc 
	$(CXX) $(CXXFLAGS) $@ $<

clean:
	rm -fr $(APP)
	rm -fr $(CPP_OBJECTS)
	rm -fr $(TESTS)
