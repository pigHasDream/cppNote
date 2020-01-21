#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Dog {
  string name_;
  public:
    Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name; }
    Dog() { cout << "Dog is created nameless: " << endl; name_ = "nameless"; }
    ~Dog() { cout << "Dog is destroyed. " << endl; }

    void bark() { cout << "Dog " << name_ << " is bark! " << endl; }
};

void foo() {

  shared_ptr<Dog> p(new Dog("Guner"));

  {
    shared_ptr<Dog> p2 = p;
    p2->bark();
    cout << "count p.use_count: " << p.use_count() << endl;
    cout << "count p2.use_count: " << p2.use_count() << endl;
  }

  p->bark();
  cout << "count p.use_count: " << p.use_count() << endl;

}

int main() {

  foo();


  // =================================
  // Below is an errorneous usage!!
  // Dog* ptr = new Dog("Tank");
  // shared_ptr<Dog> q1(ptr);
  // shared_ptr<Dog> q2(ptr);
  // =================================


  // !!!!!!!!!
  // An object should be assigned to a smart pointer as soon as it is created.
  // I.e. raw pointer should not be used!
  //
  // Below is the recommended way
  // make_shared is faster than first creating a raw pointer then assign!
  // Also it's exception safe!

  shared_ptr<Dog> q1 = make_shared<Dog>("Happy");
  shared_ptr<Dog> q2 = q1;

  cout << "count q1.use_count: " << q1.use_count() << endl;
  cout << "count q2.use_count: " << q2.use_count() << endl;


  shared_ptr<Dog> p1 = make_shared<Dog>("Gunner"); // using default deleter: operator delete when out of scope.
  shared_ptr<Dog> p2 = make_shared<Dog>("Tank");

  p1 = p2; // Gunner is deleted
  p1 = nullptr; // Gunner is deleted
  p1.reset(); // Gunner is deleted


  // !!!!!!!!!
  // if we need to use a customized deleter, need to use below to construct
  // it'll call the customized destructor!
  // This is very useful with delete []
  shared_ptr<Dog> p3 = shared_ptr<Dog>(new Dog("Tank"), 
                                       [](Dog* p) { cout << "Custom deleting." << endl; delete p; }
      );

  // once we have created shared_ptr, it should be very careful to use the raw pointer otherwise it 
  // may cause double deletion!

  return 0;
}
