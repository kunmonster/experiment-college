/**
 * fkj
 * 2021/12/14
 * 01knapsack base on branch bound
 */
#include <iostream>
#include <queue>
using namespace std;

typedef struct _GOOD_ {
  int index;
  double weight;   //重量
  double value;    //价值
  double avg_val;  //平均价值
  double up;
} good;
struct cmp {
  bool operator()(const good* a, const good* b) const { return a->up < b->up; }
};
typedef priority_queue<good*, vector<good*>, cmp> pri_que;
void sort(good* a, int n) {
  int i, j;
  bool flag = false;
  for (i = 1; i <= n - 1; i++) {
    for (j = 1; j <= n - i - 1; j++) {
      if (a[j].avg_val < a[j + 1].avg_val) {
        good temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
        flag = true;
      }
    }
    if (!flag) break;
  }
}
class KnapSack {
 private:
  good* good_arr;  //物品数组
  int n;           //物品数量
  int c;           //背包容量
  int cw;          //背包当前重量
  int cv;          //背包当前价值
  int best;
  double Bound(int);

 public:
  KnapSack(int, int);
  void Solution();
  ~KnapSack();
};
KnapSack::KnapSack(int n, int c) {
  this->n = n;
  this->c = c;
  this->good_arr = new good[n + 1];
  this->cw=0;
  this->cv=0;
  this->best=0;
  cout << "请输入物品的重量和价值:[重量] [价值]" << endl;
  for (int i = 1; i <= n; i++) {
    cin >> good_arr[i].weight >> good_arr[i].value;
    good_arr[i].avg_val = good_arr[i].value / good_arr[i].weight;
    good_arr[i].index = i;
    good_arr[i].up = 0;
  }
  sort(this->good_arr, n+1);
  for(int i=1;i<=n;i++){
    this->good_arr[i].index=i;
  }
}
double KnapSack::Bound(int index) {
  //限界函数,根据此函数修改优先队列
  int lc = this->c - this->cw;  //计算当前剩余容量
  if (lc == 0) return 0;
  int i = index;
  double best = this->cv;
  while (i <= n && this->good_arr[i].weight <= lc) {
    lc -= this->good_arr[i].weight;
    best += this->good_arr[i].value;
    this->good_arr[index].up = best;
    i++;
  }
  if (i <= n) {
    best += lc * this->good_arr[i].avg_val;
    this->good_arr[index].up = best;
    lc = 0;
  }
  return best;
}

void KnapSack::Solution() {
  //分支界限法解01背包
  pri_que p;  //大顶堆
  int i = 1;
  Bound(1);
  while (i != n) {
    int wt = this->cw + this->good_arr[i].weight;
    if (wt <= c) {
      //左子树可行,更新best,放入优先队列
      if (this->best < this->cv + this->good_arr[i].value) {
        p.push(&good_arr[2 * i]);
      }
    }
    //右子树
    if (Bound(2 * i + 1) >= best) {
      p.push(&this->good_arr[2 * i + 1]);
    }
    //选出上界最大的一个扩展
    good* x = p.top();
    p.pop();
    i = x->index;
    this->c-=x->weight;
    this->best = this->cv+this->good_arr[i].value;
    //这时候已经到下一个了
    // this->cw = x->weight;
    // this->cv = x->value;
  }
}
int main() {
  cout << "请输入物品数量和背包容量:[数量] [容量]" << endl;
  int n, c;
  cin >> n >> c;
  KnapSack* knapsack = new KnapSack(n, c);
  knapsack->Solution();
  return 0;
}