#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <ostream>

using namespace std;

/* unique_lock usage and adv
// 1. unique_lock can improve granualiry and defer the lock!
// 2. unique_lock can be moved and transferred the ownership of mutex
// 3. unique_lock is more heavy loaded than lock_guard
*/

// std::once_flag
// std::call_once(std::once_flag, []() {})
// 
// This ensured the lambda function will be called only once
// and locked only once!


class LogFile {
    std::mutex mu_;
    sted::once_flag flag_;
    ofstream f_;

  public:

    void shared_print(string id, int value) {
      // std::lock_guard<std::mutex> locker(mu_);
      std::unique_lock<std::mutex> locker(mu_, std::defer_lock);
      // do something else

      std::call_once(flag_, [&](){f_.open("log.txt"); });
      
      locker.lock();
      cout << "From " << id <<  ": " << value << endl;
      locker.unlock();
      // ... 


      locker.lock();
      // ...
      locker.unlock();
    }

};


void func1(LogFile& log) {
  for(int i=0; i>-100; --i)
    log.shared_print("t1", i);
}

int main() {
  LogFile log;
  
  std::thread t1(func1, std::ref(log));

  for(int i=0; i<100; ++i)
    log.shared_print2("main", i);

  t1.join();

  return 0;
}

