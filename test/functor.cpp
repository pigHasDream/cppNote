#include <iostream>
#include <string>
#include <vector>

using namespace std;

class X {
  int state_;

  public:
    X(int i) {state_ = i;}
    void operator() (string str) {
      cout << "calling functor X with parameter " << str << endl;
    }

    // This is a type conversion!
    // operator keywords comes before the type!!
    operator string () { cout << "X" << endl; }

};


//  Benefits of functor:
//  1. smart function: capability beyond operator()
//  It can remeber state: multiple instances behave differently
//
//  2. it can have its own type even if 2 functors share same signature
//
//  3. Also enables "parameterized function"`

template<int VAL>
void AddValueTemp(int x) {
  cout << x + VAL << endl;
}

class AddValue {
  int val_ = 0;

public:
  AddValue(int x) : val_(x) {}

  void operator()(int i) {
    cout << i + val_ << endl;
  }
};

int main() {

  vector<int> vec { 2,3,4,5};

  // This solution is using template, but it is done in compilation time
  // The value 2 has to be predetermined statically!!
  for_each(vec.begin(), vec.end(), AddValueTemp<2>);

  cout << "Split line" << endl;


  // below functor usage is much nice!
  int x=2;
  for_each(vec.begin(), vec.end(), AddValue(x));

  return 0;

}
