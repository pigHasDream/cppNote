#include <iostream>
#include <stringstream>

using namespace std;
int main () {

  string s("hello"); // random access interface, can do s[4]

  { // open mylog.txt if not exisitng, create it.
    // this is RAII

    ofstream of("mylog.txt"); // serial access, cannot do of[4]
    of << "This is correct" << endl;
    of << 23423 << endl;
    of << 2.3122 << endl;
    of << bitset<8>(14) << endl; // add bitset of 8 bit for decimal value 14
  }

  // decouple IO formmating and IO device communication
  // Softer ware design principle:
  // low coupling!!

  // ============================================================
  // stringstream: a stream has no communicating channel!
  // read/write of string!!


  return 0;
}
