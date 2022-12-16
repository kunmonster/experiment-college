#include <bits/stdc++.h>
using namespace std;

/// @brief 数组反转
/// @param array
/// @param l
/// @param r
void reverse(int* array, int l, int r) {
  int mid = (l + r) / 2;
  int i = l, j = r;
  for (i; i <= mid; ++i,--r) {
    swap(array[i], array[r]);
  }
}

/// @brief 将数组循环左移p个位置,本质上化成数组反转问题
/// @param array
/// @param p
void circulateMove(int*array, int p,int n) {
    cout<<"innerarray:"<<array<<endl;
    reverse(array,0,p-1);
    reverse(array,p,n-1);
    reverse(array,0,n-1);

}

int main() {
    int arr[5];
    cout<<"arr:"<<arr<<endl<<"&arr:"<<&arr<<endl;
    int * array = new int[10] {0,1,2,3,4,5,6,7,8,9};
    cout<<"array:"<<array<<endl<<"&array:"<<&array<<endl;
    // circulateMove(array,3,10);
    // for(int i=0;i<=9;i++){
    //     cout<<array[i]<<"\t";
    // }
}