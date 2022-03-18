/**
 * 剑指offer63 股票最大利润
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int len = prices.size();
    int* dp = new int[len]{0};
    int minval = 1e9;
    int i = 1;
    int j = 0;
    while (i < len) {
      while (j <= i) {
        if (prices[j] < minval) {
          minval = prices[j];
        }
        j++;
      }
      dp[i] = max(dp[i - 1], dp[i - 1] + (prices[i] - minval));
      i++;
    }
    return dp[i - 1];
  }
};

int main() {
  vector<int> arr = {7, 1, 5, 3, 6, 4};

  Solution solution;
  cout<<solution.maxProfit(arr);

  return 0;
}