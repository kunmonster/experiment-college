#include<bits/stdc++.h>
using namespace std;

class MyString{
  public:
  MyString();
  MyString(const char * s);
  ~MyString();
};

int main(){
  MyString("hello");
  return 0;
}