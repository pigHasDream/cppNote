#include <iostream>


using namespace std;

class Base {
  public:
    Base() { cout << "Constructor" << endl; }
    ~Base() { cout << "Destructor" << endl; }
};

int main() {
  // normal usage:
  // each 'new' call will switch context from user mode
  // to kernel mode, henc expensive.

  cout << "====== Normal case ======" << endl;
  Base* obj = new Base();
  delete obj;

  // placement new case:
  // It pre-allocate a chunk of memory from kernel
  // then holds it by pointer
  // Later 'new' calls will come from this pointer

  cout << "====== Placement new case ======" << endl;

  char* memory = new char[10*sizeof(Base)];

  Base* obj1 = new (&memory[0]) Base();
  Base* obj2 = new (&memory[4]) Base();
  Base* obj3 = new (&memory[8]) Base();
  
  obj1->~Base();
  obj2->~Base();
  obj3->~Base();

  delete [] memory;
  return 0;
}
