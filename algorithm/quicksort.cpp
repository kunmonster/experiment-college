#include<iostream>
using namespace std;
void quicksort(int * arr ,int start,int endb);
int main(){    
    int arr[10] = {6,3,7,2,9,1,8,4,5,10};
    quicksort(arr,0,9);
    for(int i = 0;i<10;i++){
        std::cout<<arr[i]<<"\t";
    }
    return 0;
}
void quicksort(int * arr,int start,int end){
    //exit
    if(!arr || start >= end){
        return ;
    }   
    int base = *(arr+start);
    int i = start;
    int j = end;
    while( i < j){
    while(i < j && *(arr+j) > base){
        j--;
    }
    *(arr+i) = *(arr+j);
    while(i < j && *(arr+i) < base){
        i++;
    }
    *(arr+j) = *(arr+i);
    }
    *(arr+i) = base;
    quicksort(arr,start,i-1);
    quicksort(arr,i+1,end);
}