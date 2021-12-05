#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct _GOOD_ {
  /* data */
  int weight;
  int value;
  double average_value;
} good;

struct cmp {
  bool operator()(const good a, const good b) {
    return a.average_value > b.average_value;
  }
};

void sort(good* a, int n) {
  int i, j;
  bool flag = false;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (a[j].average_value < a[j + 1].average_value) {
        good temp = a[i];
        a[j] = a[j+1];
        a[j+1] = temp;
        flag = true;
      }
    }
    if (!flag) break;
  }
}

class knapsack {
 private:
  //上界函数
  double bound(int i);
  good* good_arr;      //重量数组
  bool* res;           //结果数组
  int num;             //物品数量
  int capacity;        //背包容量
  int best_value;      //最大价值
  int current_weight;  //当前背包重量
  int current_value;   //当前背包价值

 public:
  knapsack(good*, int, int);
  void getBestMatch(int);
  void getResult();
  ~knapsack();
};

knapsack::knapsack(good* good_arr, int num, int capacity) {
  this->good_arr = new good[num];
  this->good_arr = good_arr;
  this->capacity = capacity;
  this->current_value = 0;
  this->current_weight = 0;
  this->best_value = 0;
  this->num = num;
  this->res = new bool[this->num]{false};
}

knapsack::~knapsack(){};

double knapsack::bound(int index) {
  if (!this->good_arr) return 0;

  //
  int left_c = this->capacity - this->current_weight;
  double cv = this->current_value;

  int i;
  int len = num - index;
  good temp[len];
  for (i = 0; i < len; i++) {
    temp[i] = good_arr[i + index];
  }
  sort(temp, len);
  i = 0;
  while (i < len && temp[i].weight <= left_c) {
    left_c -= temp[i].weight;
    cv += temp[i].value;
    i++;
  }
  if (i < len) {
    cv += left_c * temp[i].average_value;
    left_c = 0;
  }

  return cv;
}
void knapsack::getBestMatch(int index) {
  //回溯
  if (index > this->num - 1) {
    this->best_value = this->current_value;
    this->res[index] = true;
    return;
  }
  if ((this->current_weight + this->good_arr[index].weight) <= this->capacity) {
    //左子树
    current_value += this->good_arr[index].value;
    current_weight += this->good_arr[index].weight;
    res[index] = true;
    getBestMatch(index + 1);
    current_value -= this->good_arr[index].value;
    current_weight -= this->good_arr[index].weight;
  }
  double bound_c = this->bound(index + 1);
  if (bound_c > best_value) {
    this->res[index] = false;
    getBestMatch(index + 1);
  }
}

void knapsack::getResult() {
  if (this->res) {
    cout << "装入背包最大价值为:" << this->best_value << endl;
    int size = this->num;
    cout << "装入背包的物品序号为:" << endl;
    for (int i = 0; i < size; i++) {
      if (res[i]) {
        cout << i << "\t";
      }
    }
  }
}

int main() {
  cout << "请输入物品个数,背包容量 : [物品个数] [容量]" << endl;
  int n, c;
  cin >> n >> c;
  good* good_arr = new good[n];
  int weight, value;
  cout << "请输入每个物品的重量和价值 : [重量] [价值]" << endl;
  for (int i = 0; i < n; i++) {
    cin >> weight >> value;
    good_arr[i].weight = weight;
    good_arr[i].value = value;
    good_arr[i].average_value = value / (double)weight;
  }
  knapsack* sol = new knapsack(good_arr, n, c);
  sol->getBestMatch(0);
  sol->getResult();
  return 0;
}