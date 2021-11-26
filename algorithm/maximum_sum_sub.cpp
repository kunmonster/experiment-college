#include<iostream>
#include<algorithm>
using namespace std;
int get_max(int *,int *,int );
int main(){
  return 0;
}
int get_max(int * arr,int * maxsum,int len){
  if(! arr){
    return 0;
  }
  int i,j;
  for(i=0;i<len;i++){
    maxsum[i] = 0;
  }
  for(i = 1;i<len;i++){
    maxsum[i] = max(maxsum[i-1]+arr[i],arr[i]);
  }

}