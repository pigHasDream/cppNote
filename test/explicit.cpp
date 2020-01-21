#include<iostream>

using namespace std;

class A {
  int a_;
  public:
    explicit A(int val) {
      a_ = val;
      cout << "A constructor" << endl;
    }
};

void func(A a) {

}

int main() {

  func(10);

  return 0;
}
