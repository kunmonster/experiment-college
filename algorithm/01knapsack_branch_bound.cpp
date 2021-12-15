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
} good;

typedef struct _NODE_ {
  struct _NODE_* parent;  //父节点
  int left;               //左子节点
  double up;              //此节点上界
  int value;              //此节点时背包的价值
  int weight;             //此节点时背包的重量
  int lev;                //此节点索引
} node;

struct cmp {
  //构造优先队列时候的比较
  bool operator()(const node* a, const node* b) const { return a->up < b->up; }
};

typedef priority_queue<node*, vector<node*>, cmp> pri_que;

/**
 * 添加节点进入优先队列
 */
void AddNode(pri_que& p, node* E, int wt, int up, int value, int i, int lc) {
  node* a = (node*)malloc(sizeof(node));
  a->parent = E;
  a->left = lc;
  a->up = up;
  a->value = value;
  a->weight = wt;
  a->lev = i + 1;
  p.push(a);
}

/**
 * 初始化的时候排序(buddle)
 */
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
  good* good_arr;     //物品数组
  int n;              //物品数量
  int c;              //背包容量
  int cw;             //背包当前重量
  int cv;             //背包当前价值
  int best;           //最优价值
  int* res;           //最优组合
  double Bound(int);  //上界计算函数

 public:
  KnapSack(int, int);
  void Solution();
  void Print();
  ~KnapSack();
};
KnapSack::KnapSack(int n, int c) {
  this->n = n;
  this->c = c;
  this->good_arr = new good[n + 1];
  this->res = new int[n + 1]{0};
  this->cw = 0;
  this->cv = 0;
  this->best = 0;
  cout << "请输入物品的重量和价值:[重量] [价值]" << endl;
  for (int i = 1; i <= n; i++) {
    cin >> good_arr[i].weight >> good_arr[i].value;
    good_arr[i].avg_val = good_arr[i].value / good_arr[i].weight;
    good_arr[i].index = i;
  }
  sort(this->good_arr, n + 1);
  for (int i = 1; i <= n; i++) {
    this->good_arr[i].index = i;
  }
}
double KnapSack::Bound(int index) {
  //限界函数,根据此函数修改优先队列
  int lc = this->c - this->cw;  //计算当前剩余容量
  if (lc == 0) return 0;
  int i = index;
  double up = this->cv;
  while (i <= n && this->good_arr[i].weight <= lc) {
    lc -= this->good_arr[i].weight;
    up += this->good_arr[i].value;
    i++;
  }
  if (i <= n) {
    up += lc * this->good_arr[i].avg_val;
    lc = 0;
  }
  return up;
}

void KnapSack::Solution() {
  //分支界限法解01背包
  pri_que p;  //大顶堆
  int i = 1;
  node* E = NULL;
  double up = Bound(1);
  while (i != n + 1) {
    int wt = this->cw + this->good_arr[i].weight;
    if (wt <= this->c) {
      //左子树可行,更新best,放入优先队列
      if (this->best < this->cv + this->good_arr[i].value) {
        this->best = this->cv + this->good_arr[i].value;
      }
      AddNode(p, E, this->cw + this->good_arr[i].weight, up,
              this->cv + this->good_arr[i].value, i, 1);
    }
    //右子树
    up = Bound(i + 1);
    if (up >= best) {
      AddNode(p, E, this->cw, up, this->cv, i, 0);
    }
    //选出上界最大的一个扩展
    E = p.top();
    p.pop();
    this->cw = E->weight;
    this->cv = E->value;
    up = E->up;
    i = E->lev;
  }
  for (int j = n; j >= 1; --j) {
    this->res[this->good_arr[E->lev - 1].index] = E->left;
    E = E->parent;
  }
}
void KnapSack::Print() {
  cout << "背包最大价值为:" << this->best << endl;
  cout << "组合为:" << endl;
  for (int i = 1; i <= n; i++) {
    if (this->res[i] == 1) cout << i << "\t";
  }
}
int main() {
  cout << "请输入物品数量和背包容量:[数量] [容量]" << endl;
  int n, c;
  cin >> n >> c;
  KnapSack* knapsack = new KnapSack(n, c);
  knapsack->Solution();
  knapsack->Print();
  return 0;
}