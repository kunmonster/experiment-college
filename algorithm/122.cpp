#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int size = prices.size();
    if (size <= 1) return 0;
    int slow = 0;
    int fast = 1;
    int maxP = 0;
    while (fast < size) {
      if (prices[fast] >= prices[fast - 1])
        fast++;
      if((prices[fast] >= prices[fast-1]) && (fast==size-1)){
        maxP += (prices[fast] - prices[slow]);
        break;
      }
      if(prices[fast] < prices[fast-1]) {
        maxP += (prices[fast - 1] - prices[slow]);
        slow = fast;
        fast++;
      }
    }
    
    return maxP;
  }
};
int main() {
  vector<int> arr{1,2};
  Solution a;
  cout << a.maxProfit(arr);
}