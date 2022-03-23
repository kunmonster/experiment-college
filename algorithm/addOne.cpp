/**
 * data : 2022.3.23
 *
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    if (digits[0] == 0) return {1};
    int i = digits.size() - 1;
    while (i >= 0) {
      if(digits[i] != 9){
        digits[i]++;
        return digits;
      }
      else{
        digits[i]=0;
      }
      i--;
    }
    digits[0]=1;
    digits.push_back(0);
    return digits;
  }
};
int main() {
  vector<int> arr{9, 0, 9};
  Solution a;
  a.plusOne(arr);
  return 0;
}