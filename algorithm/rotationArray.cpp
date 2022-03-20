#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(k==0) return;
        int size = nums.size();
        int index = 0;
        int temp = nums[0];
        bool * arr = new bool[size]{false};

        int i=0;
        while(i<size){
            index = (index+k) % (size);
            if(!arr[index]){
            swap(nums[index],temp);
            arr[index]= true;
            }
            else {
              index = (index+1) % size;
              temp = nums[index];
            }
            i++;            
        }
        
    }
};
int main(){
  vector<int>arr{-1,-100,3,99};
  Solution a;
  a.rotate(arr,2);
  
  return 0;
}