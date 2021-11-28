#include<iostream>
using namespace std;

struct Bit {
  unsigned x7 : 1;
  unsigned x6 : 1;
  unsigned x5 : 1;
  unsigned x4 : 1;
  unsigned x3 : 1;
  unsigned x2 : 1;
  unsigned x1 : 1;
  unsigned x0 : 1;
  Bit(int x7,int x6,int x5,int x4,int x3,int x2,int x1,int x0) : x7(x7),x6(x6),x5(x5),x4(x4),x3(x3),x2(x2),x1(x1),x0(x0) {}
  Bit(int x6,int x5,int x4,int x3,int x2,int x1,int x0) : x6(x6),x5(x5),x4(x4),x3(x3),x2(x2),x1(x1),x0(x0) {}
  Bit(int x5,int x4,int x3,int x2,int x1,int x0) : x5(x5),x4(x4),x3(x3),x2(x2),x1(x1),x0(x0) {}
  Bit(int x4,int x3,int x2,int x1,int x0) : x4(x4),x3(x3),x2(x2),x1(x1),x0(x0) {}
  Bit(int x3,int x2,int x1,int x0) : x3(x3),x2(x2),x1(x1),x0(x0) {}
  Bit(int x2,int x1,int x0) : x2(x2),x1(x1),x0(x0) {}
  Bit(int x1,int x0) : x1(x1),x0(x0) {}
  Bit(int x0) : x0(x0) {}
};


int main(){
  struct Bit a(1);
  cout<<sizeof(a);
  return 0;
}