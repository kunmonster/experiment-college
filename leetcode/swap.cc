#include<bits/stdc++.h>
using namespace std;


void swap(int * &a, int  * & b){
    auto tmp = a;
    a = b;
    b = tmp;
    tmp  = NULL;
}


int main(){
    int a = 10;
    int b = 20;
    int * p_a = &a;
    int *p_b= &b;
    cout<<"a:"<<p_a<<endl<<"b:"<<p_b<<endl;
    swap(p_a,p_b);
    cout<<"a:"<<p_a<<endl<<"b:"<<p_b<<endl;


    return 0;
}