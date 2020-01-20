#include <iostream>
#include <thread>
#include <string>
#include <functional>
#include <utility>
#include <mutex>

using namespace std;

/* 
 * avoiding data race:
 *
 * 1. use mutex to synchronize data access (not barefoot mutex)
 * 2. never leak a handle of data (the shared data) to outside
 * 3. Deisgn interface properly (for atomic actions)
 *
*/

std::mutex mu;

// use mutex to deal with COMMON RESOUCE!
void shared_print(string msg, int id) {
  // barefoot mutex cannot receive exception!
  // mu.lock();

  std::lock_guard<std::mutex> guard(mu);
  cout << msg << id << endl;
}

void func1(int bnd) {
  for(int i=0; i>-bnd; --i)
    shared_print("From t1: ",i);
}


int main() {

  std::thread t1(func1, 100);

  for(int i=0; i<100; ++i)
    shared_print("From main: ",i);

  t1.join();
  return 0;

}
