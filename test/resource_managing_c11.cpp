#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>

// This is the solution from Cpp 11 with more weapon!

// ---------------------------------------------------------
// Any time one class owns object of another class through 
// pointers, we need to take care of the deep copy thing!
// Solutions are
// 1. Either explicitly define copy/assignment constructor 
// to do a deep copy! ---> not recommended!
//
// 2. Delete the copy/assignment constructor, and explicitly
// define a clone function that returns a new pointer of the
// deeply copied object of current one! ---> recommended!
//
//
// C++11
// 1. use unique_ptr to automatically take care of deletion
// 2. use default move constructor
// 3. use std::move for moving the p


using namespace std;

class Person {
  public:
    Person(string name) : pName_{new string(name)} {}
    void printName() { cout << *pName_ << endl; }
    Person(Person&& other) = default;

  private:
    Person(const Person& other) = delete;
    Person& operator=(const Person& other) = delete;
    unique_ptr<string> pName_;
};

int main() {

  vector<Person> persons;
  Person p("George");
  persons.emplace_back(std::move(p));
  persons.back().printName();
  cout << "Bye" << endl;
  return 0;
}
