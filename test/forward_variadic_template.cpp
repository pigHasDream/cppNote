#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

// test for function tempalte
void goo(string&& str) {
  cout << "rvalue reference " << str << endl;
}

void goo(string& str) {
  cout << "lvalue reference " << str << endl;
}

void goo(string&& str, int a) {
  cout << "lvalue reference_ " << a << str << endl;
}

template<class ... Arg>
void func(Arg&& ... args) {
  goo(forward<Arg>(args) ...); 
}

template<class T, class ... Arg>
T func(Arg&& ... args) {
  return T(forward<Arg>(args) ...); 
}

int main() {

  func("Hello");
  func("Hello", 10);

  int a = 10;
  a = func<int>(a);
  cout << a << endl;

  return 0;
}
