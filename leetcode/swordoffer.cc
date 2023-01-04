#include <bits/stdc++.h>
using namespace std;



//剑指58 左旋转字符串
string reverseLeftWords(string s,int n){
    reverse(s,0,s.length()-1);
    reverse(s,0,s.length()-n-1);
    reverse(s,s.length()-n,s.length()-1);
    return s;

}

void reverse(string & str,int low,int high){
    while(low < high){
        swap(str[low] ,str[high]);
        ++low;
        --high;
    }
}





int main(int argc, char** argv) {
    return 0;
}