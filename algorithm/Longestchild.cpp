#include<iostream>
#include<stack>
using namespace std;

class solution{
  public:
  solution();
  string getTheLongest(string origin);
};

string solution::getTheLongest(string origin){
  int length = origin.length();
  if(length == 0){
    return "";
  }
  else{
    stack<int> carry;
    for(int i=0;i<length;i++){
      if(carry.empty()){
        carry.push(i);
      }
      if( origin[i] == ')' && origin[carry.top()] == '(' ){
        carry.pop();
        
      }
    }
  }
}

int main(){

  system("pause");
  return 0;
}