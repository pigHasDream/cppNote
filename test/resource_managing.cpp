#include <iostream>
#include <utility>
#include <vector>
#include <string>

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


using namespace std;

class Person {
  public:
    Person(string name) { pName_ = new string(name); }
    ~Person() { delete pName_; }
    // Best practice is to avoid copy and assignment constructor
    // as they are rarely used in practice! Mostly moving around!
    // Also the copy/assignment is implicit, so easy to make error!
    //
    // Can use clone function to explicitly clone an object
    //
    //Person(const Person& other) { pName_ = new string(*other.pName_); }
    //Person& operator=(const Person& other) { 
    //  pName_ = new string(*other.pName_);
    //  return *this;
    //}

    Person* clone() {
      if(pName_ == nullptr)
        return nullptr;

      return new Person(*pName_);
    }
    void printName() { cout << *pName_ << endl; }

  private:
    Person(const Person& other) = delete;
    Person& operator=(const Person& other) = delete;
    string * pName_;
};

int main() {

  vector<Person*> persons;
  persons.push_back(new Person("George"));
  persons.back()->printName();
  cout << "Bye" << endl;
  return 0;
}
