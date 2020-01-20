#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <ostream>

using namespace std;

class LogFile {
  std::mutex mu_;
  std::mutex mu2_;

  public:

  void shared_print(string id, int value) {
    // lock mu_ first then mu2_ this creates deadlock
    std::lock_guard<std::mutex> locker(mu_);
    std::lock_guard<std::mutex> locker2(mu2_);

    cout << "From " << id <<  ": " << value << endl;
  }
  void shared_print2(string id, int value) {
    // lock mu2_ first then mu_ => this creates deadlock
    std::lock_guard<std::mutex> locker2(mu2_);
    std::lock_guard<std::mutex> locker(mu_);

    cout << "From " << id <<  ": " << value << endl;
  }

};


/* avoid deadlock
 * 
 * 1. prefer locking only single mutex!
 * 2. avoid locking a mutex and then calling a user provided function
 *    There maybe other mutex locking inside the user function to cause deadlock
 *
 * 3. use std::lock() to lock more than one mutex, it has algo to avoid deadlock
 * 4. lock mutex in same order in all the calls!
 *
 */

// Locking granualarity
// 1. Finegrained: may cause deadlock
// 2. Coarsegrained: may be suboptimal on concurrency



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

