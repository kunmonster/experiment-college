#include<bits/stdc++.h>
using namespace std;

 int binFind(vector<int> &nums,int target){
        int size = nums.size();
        if(size == 0) return -1;
        int left=0,right = size-1;
        int mid = 0;
        while(left <= right){
        mid = (left+right) /2;
        if(nums[mid] == target){
            return mid;
        }
        else if(nums[mid] < target){
            left = mid+1;
        }
        else {
            right = mid-1;
        }
    }
    return -1;
    }
int search(vector<int>& nums, int target) {
        int count = 0;
        int size = nums.size();
        int index = binFind(nums,target);
        int right_index = index+1;
        if(index != -1){
          index--;
        while(index>=0){
            if(nums[index] == target){
                count++;
            }
            index--;
        }
        while(right_index<size){
            if(nums[right_index] == target){
                count++;
            }
            right_index++;
        }
        count++;
        }
        return count;
    }
   
int main(){
  vector<int> s{5,7};
  cout<<search(s,2);
  
  return 0;
}