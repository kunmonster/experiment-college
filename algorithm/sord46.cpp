#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int translateNum(int num) {
        string str = to_string(num);
        //p为从第一个元素到当前元素的前一个的种数
        //q为从第一个元素到当前元素前两个的种数
        int p = 1,q = 1,res=0;
        
        int size = str.size();
        for(int i=1;i<size;i++){
            //
            if((int)str[i-1] > 2){
                res = p;
            }
            else{
                if((int)str[i] > 5){
                    res = p;
                }
                else{
                    res = p + q;
                
                }
            }
            q = p;
            p = res;
            
        }
        return res;
  }
};

int main(){
  Solution solution;
  solution.translateNum(25);
  return 0;
}