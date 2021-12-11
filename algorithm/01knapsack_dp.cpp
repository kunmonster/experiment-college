/**
 * fkj
 * 2021/12/11
 * 01 knapsack base dynamic planning
 */
#include <algorithm>
#include <iostream>

using namespace std;

class KnapSack {
 private:
  int capacity;  //背包容量
  int n;         //物品个数
  int* w;        //重量数组
  int* v;        //价值数组
  int** dp;      //最大值存放
 public:
  KnapSack(int, int);
  void Solution();
  ~KnapSack();
};

KnapSack::KnapSack(int n, int c) {
  this->n = n;
  this->capacity = c;
  cout << "请输入物品的重量和价值:[重量] [价值]" << endl;
  this->w = new int[n + 1]{0};
  this->v = new int[n + 1]{0};
  int s_w = 0, s_v = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s_w >> s_v;
    w[i] = s_w;
    v[i] = s_v;
  }
  this->dp = new int*[n + 1];
  for (int i = 0; i <= n; i++) {
    this->dp[i] = new int[c+1]{0};
  }
}
void KnapSack::Solution() {
  int i, j;
  for (i = 1; i <= this->n; i++) {
    for (j = 1; j <= this->capacity; j++) {
      if (j < this->w[i]) {
        //容量不足以放物品,这时候最大价值就是子问题
        this->dp[i][j] = dp[i-1][j];
      } else {
        this->dp[i][j] = max(this->dp[i-1][j - this->w[i]] + this->v[i],
                             this->dp[i-1][j]);
      }
    }
  }
}

int main() {
  KnapSack* knapsack = new KnapSack(5, 10);
  knapsack->Solution();
  return 0;
}