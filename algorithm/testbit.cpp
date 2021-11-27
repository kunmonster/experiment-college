#include<iostream>
using namespace std;
struct Bit{
  unsigned a : 1;
};

int main(){
  struct Bit a;
  a.a = 0;
  cout<<sizeof(a);
  return 0;
}