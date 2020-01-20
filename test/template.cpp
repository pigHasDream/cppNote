#include <iostream>
#include <vector>

using namespace std;

template < class T> 
class BoVector {
  vector<T> arr_;
  int size_;

  public:
  BoVector() : size_(0) {
    arr_.resize(10000, 0);
  }
  void push(T x) { arr_[size_] = x; ++size_; }
  T get(int i) const { return arr_[i]; }
  int getSize() const { return size_; }
  void print() const { 
    for(int i=0; i<size_; ++i)
      cout << arr_[i] << endl;
  }
};

// Not all operator overloading is allowed for global or static member functions!
// operator(), = etc must be non-static member function!
template <class T>
BoVector<T> operator* (const BoVector<T>& a, const BoVector<T>& b) {
  BoVector<T> res;
  for(int i=0; i<a.getSize(); ++i)
    res.push(a.get(i) * b.get(i));

  return res;
}

template<class T>
T square(T x) {
  return x*x;
}

int main() {
  BoVector<int> bv;
  bv.push(2);
  bv.push(4);
  bv.push(8);
  bv.push(9);

  cout << "Print squared vector" << endl;
  bv = square(bv);
  bv.print();

  return 0;
}
