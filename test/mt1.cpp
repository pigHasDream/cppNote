#include <iostream>
#include <thread>
#include <string>
#include <functional>
#include <utility>

using namespace std;

void func1() {
  cout << "Hello this is func1" << endl;
}

class Fctor {
  public:
    void operator()(string msg) {
      cout << "t1 says: " << msg << endl;
      msg = "Trust is the mother of deceit.";
    }
};


int main() {

  string  s = "where there is no trust, there is no love";
  cout << std::this_thread::get_id() << endl;

  // by default std::thread always takes a copy or move of the parameters
  // if we want to use reference, we have to use std::ref(), so that there 
  // establishes a shared memory between threads!

  std::thread t1((Fctor()), std::move(s)); // thread t1 starts running
  cout << t1.get_id() << endl;

  std::thread t2 = std::move(t1);
  cout << t2.get_id() << endl;

  t2.join();

  return 0;

}
