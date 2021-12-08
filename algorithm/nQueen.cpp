/**
 *fkj
 *2021/12/05
 *回溯n后
 */
#include <string.h>

#include <iostream>
#include <vector>

using namespace std;

class Nqueen {
 private:
  bool place(int);  //限界函数
  int n;            //棋盘的行列数
  int* res;         //结果数组，res[i]表示第i行存放的列数
  int sum;
  vector<vector<string>>* res_arr;

 public:
  Nqueen(int);
  ~Nqueen();
  void BackTrack(int);
  void Print();
  void BackTrack_iterator();
};

Nqueen::Nqueen(int n) {
  this->n = n;
  this->res = new int[n + 1]{0};
  this->sum = 0;
  this->res_arr = new vector<vector<string>>();
}
Nqueen::~Nqueen() { cout << "析构调用"; }

bool Nqueen::place(int index) {
  for (int i = 1; i < index; i++) {
    if (abs(index - i) == abs(this->res[i] - this->res[index]) ||
        (this->res[i] == this->res[index]))
      return false;
  }
  return true;
}
void Nqueen::BackTrack(int index) {
  if (index > this->n) {
    this->sum++;
    vector<string> temp(n + 1);
    for (int i = 1; i <= this->n; i++) {
      for (int j = 1; j <= this->n; j++) {
        if (res[i] != j) {
          temp[i].append(". ");
        } else {
          temp[i].append("Q ");
        }
      }
    }
    this->res_arr->push_back(temp);
    return;
  } else {
    for (int i = 1; i <= this->n; i++) {
      res[index] = i;
      if (place(index)) {
        BackTrack(index + 1);
      }
    }
  }
}
void Nqueen::Print() {
  cout << "总共有" << sum << "种解如下:" << endl;
  int size = this->res_arr->size();
  for (int i = 0; i < size; i++) {
    for (int j = 1; j <= this->n; j++) {
      cout << this->res_arr->at(i)[j] << endl;
    }
    cout << endl;
  }
}

void Nqueen::BackTrack_iterator() {
  //迭代版本
  int row = 1;

  while (row >= 1) {
    this->res[row]++;
    while (this->res[row] <= n && !place(row)) res[row]++;
    if (this->res[row] <= n) {
      if (row == n) {
        //找到解
        vector<string> temp(n + 1);
        for (int i = 1; i <= this->n; i++) {
          for (int j = 1; j <= this->n; j++) {
            if (res[i] != j) {
              temp[i].append(". ");
            } else {
              temp[i].append("Q ");
            }
          }
        }
        this->res_arr->push_back(temp);
        sum++;
      } else {
        //还未到n行,但在此行找到存放的位置
        row++;
      }
    } else {
      //在当前行没找到合适的位置存放,回溯,将上一行的滑动
      this->res[row] = 0;
      row--;
    }
  }
}

int main() {
  int a;
  cin >> a;
  Nqueen* nqueen = new Nqueen(a);
  // nqueen->BackTrack(1);
  nqueen->BackTrack_iterator();
  nqueen->Print();
  return 0;
}
