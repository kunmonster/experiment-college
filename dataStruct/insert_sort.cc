#include<bits/stdc++.h>
using namespace std;

/***
 * 直接插入排序,升序
 * para : 数组,数组长度
 * **/
void stright_insert_sort(int * arr,int len){
    if(len <= 1 ) return;
    //set the first element as the standard
    int guard = 0;
    int j=0;
    for(int i=1;i<len;i++){
        if(*(arr+i) < *(arr+i-1)){
            //当前元素小于前一个元素
            guard = *(arr+i); 
            for(j=(i-1);j>=0 && arr[j] >= arr[i];--j) arr[j+1] = arr[j];
            arr[j+1] = guard; 
        }
    }
}

int main(){
    int * arr = new int[10]{9,1,3,4,5,6,5,1,6,7};
    stright_insert_sort(arr,sizeof(arr) / sizeof(int));
    cout<<sizeof(*(&arr));
    return 0;
}