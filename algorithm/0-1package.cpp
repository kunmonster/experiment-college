#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> good;
typedef pair<int, double> good_average;

struct cmp {
  bool operator()(good_average a, good_average b) {
    return a.second < b.second;
  }
};

class knapsack {
 private:
  //上界函数
  double bound(int i);
  vector<good>* good_arr;  //重量数组
  bool* res;               //结果数组
  int num;                 //物品数量
  int capacity;            //背包容量
  int best_value;          //最大价值
  int current_weight;      //当前背包重量
  int current_value;       //当前背包价值

 public:
  knapsack(vector<good>*, int);
  void getBestMatch(int);
  void getResult();
  ~knapsack();
};

knapsack::knapsack(vector<good>* good_arr, int capacity) {
  this->good_arr = new vector<good>();
  this->good_arr = good_arr;
  this->capacity = capacity;
  this->current_value = 0;
  this->current_weight = 0;
  this->best_value = 0;
  this->num = this->good_arr->size();
  this->res = new bool[this->num]{false};
}

knapsack::~knapsack(){};

double knapsack::bound(int index) {
  if (!this->good_arr) return 0;

  priority_queue<good_average, vector<good_average>, cmp> pri_que;
  for (int i = index; i < this->num; i++) {
    good temp = this->good_arr->at(i);
    pri_que.push(
        pair<int, double>(temp.first, temp.second / (double)temp.first));
  }
  //
  int c = this->capacity;         //当前容量
  int cw = this->current_weight;  //当前重量
  double cv = this->current_value;
  while (!pri_que.empty() && c >= 0) {
    good_average temp = pri_que.top();
    if (temp.first + cw <= c) {
      //该物品能装
      //装入
      cw += temp.first;
      c -= temp.first;
      cv += temp.first * temp.second;
    } else {
      //该物品重量加上过后超过了背包的容量
      //对该物品分割
      int sub = c - cw;
      cv += sub * temp.second;
      c = this->capacity;
      break;
    }
  }
  return cv;
}
void knapsack::getBestMatch(int index) {
  //回溯
  if (index >= this->num) {
    this->best_value = this->current_value;
    this->res[index] = true;
    return;
  }
  if ((this->current_weight + this->good_arr->at(index).first) <=
      this->capacity) {
    //左子树
    current_value += this->good_arr->at(index).second;
    current_weight += this->good_arr->at(index).first;
    res[index] = true;
    getBestMatch(index + 1);
    current_value -= this->good_arr->at(index).second;
    current_weight -= this->good_arr->at(index).first;
  }
  int bound_c = this->bound(index + 1);
  if (bound_c > best_value) {
    res[index] = false;
    getBestMatch(index + 1);
  }
}

void knapsack::getResult() {
  if (this->res) {
    int size = this->num;
    for (int i = 0; i < size; i++) {
      if(res[i]){
        cout<<i<<"\t";
      }
    }
  }
}

int main() {
  int n, c;
  cin >> n >> c;
  vector<good> good_arr;
  good_arr.resize(n);
  int weight, value;
  for (int i = 0; i < n; i++) {
    cin >> weight >> value;
    good_arr[i] = pair<int, int>(weight, value);
  }
  knapsack* sol = new knapsack(&good_arr, c);
  sol->getBestMatch(0);
  sol->getResult();
  return 0;
}