#include <iostream>
using namespace std;

int main() {
  unsigned int a = 20;
  cout<<"unsinged:"<<std::hex<<a<<endl;
  int m = a;
  cout<<"int:"<<std::hex<<m<<endl;

  int c = -m;
  cout<<"-int:"<<std::hex<<c<<endl;

  unsigned int d = c;

  cout<<"- to unsinged int :"<<std::hex<<d<<endl;
  

  int i=0;

  return 0;
}