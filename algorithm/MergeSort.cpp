/**
 *author : fengkunjiang
 *fun : MergeSort based on recursion
 *date : 2021-10-1
**/

#include<iostream>
using namespace std;

void Sort(int * arr,int * reg,int start,int end){
  if(start >= end) return;          //递归出口
  int len = end - start;
  int start1 = start , mid = (len>>1)+start;
  int end1 = mid , start2 = mid + 1 , end2 = end;
  Sort(arr,reg,start1,end1);      //左半部分递归排序
  Sort(arr,reg,start2,end2);      //右半部分递归排序
  int k = start;
  while(start1 <= end1 && start2 <= end2){
    //自底向上合并
    reg[k++] = arr[start1] <= arr[start2] ? arr[start1++] : arr[start2++];         //比较相邻两个元素 
  }
  while(start1 <= end1){
    //未归并完的元素，此时元素是有序的
    reg[k++] = arr[start1++];
  }
  while(start2 <= end2){
    reg[k++] = arr[start2++];
  }
  //此步很关键，因为要将原数组覆盖不然，上面比较的时候源数组并未改变，导致比较出错
  for(k = start;k<=end;k++){
    *(arr+k) = *(reg+k);
  }
}

// int main(){
//   int arr[6] = {5,8,4,6,3,9};
//   int * reg = new int[6];
//   Sort(arr,reg,0,5);
//   int i = 0;
//   while(i<=5){
//     cout<<*(reg+i);
//     i++;
//   }
//   return 0;
// }