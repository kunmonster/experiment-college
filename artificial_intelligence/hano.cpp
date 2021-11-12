#include <iostream>
using namespace std;

void hanoi(int,char,char,char);
void move(char,char);

int main(){
	int n;
	cout<<("请输入n的值：");
	cin>>n;
	hanoi(n,'a','b','c');
	return 0;
}
void hanoi(int n,char x,char y,char z){
	if(n==1){
		move(x,z);
	}
	else{
		hanoi(n-1,x,z,y);
		move(x,z);
		hanoi(n-1,y,x,z);
	}
}
void move(char c1,char c2){
  cout<<c1<<"=======>"<<c2<<endl;
}