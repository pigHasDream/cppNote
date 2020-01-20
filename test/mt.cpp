#include <iostream>
#include <thread>
#include <string>
#include <functional>

using namespace std;

void func1() {
  cout << "Hello this is func1" << endl;
}

class Fctor {
  public:
    void operator()(string& msg) {
      cout << "t1 says: " << msg << endl;
      msg = "Trust is the mother of deceit.";
    }
};


int main() {

  string  s = "where there is no trust, there is no love";

  // by default std::thread always takes a copy or move of the parameters
  // if we want to use reference, we have to use std::ref(), so that there 
  // establishes a shared memory between threads!

  std::thread t1((Fctor()), std::ref(s)); // thread t1 starts running

  t1.join();

  cout << "from main: " << s << endl;
  return 0;

}
