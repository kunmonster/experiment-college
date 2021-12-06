/**
 *fkj
 *2021/12/05
 *回溯n后
 */
#include <iostream>
using namespace std;

class Nqueen {
 private:
  bool place(int);  //限界函数
  int n;            //棋盘的行列数
  int* res;         //结果数组，res[i]表示第i行存放的列数
  int sum;
 public:
  Nqueen(int);
  ~Nqueen();
  void BackTrack(int);
};

Nqueen::Nqueen(int n) {
  this->n = n;
  this->res = new int[n + 1]{0};
  this->sum=0;
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
int main() {
  int a;
  cin >> a;
  Nqueen* nqueen = new Nqueen(a);
  nqueen->BackTrack(1);
  return 0;
}
