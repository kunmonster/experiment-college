#include<iostream>
using namespace std;
void quicksort(int * ,int ,int);
int main(){    
    int  arr[10] = {6,3,7,2,9,1,8,4,5,10};
    quicksort(arr,0,9);
    for( int item : arr){
        cout<<item<<endl;
    }
    return 0;
}
void quicksort(int * arr,int start,int end){
    if(!arr||(start == end)){
        exit(1);
    }
    int start_num = start;
    int end_num = end;
    int base = arr[start_num];
    for(int i=start_num;i<end_num;i++){
        if(*(arr+i) > base){
            for(int j=end_num;i<=j;j--){
                if(*(arr+j) < base){
                    int temp = arr[i];
                    *(arr+i) = *(arr+j);
                    *(arr+j) = temp;
                    start_num++;
                    end_num--;
                    break;
                }
            }
        }
    }
    quicksort(arr,start,end_num);
}