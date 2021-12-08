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
  void Print(){
    cout<<"总共有"<<sum<<"种解如下:"<<endl;
    int size = this->res_arr->size();
    for(int i=0;i<size;i++){
      for(int j=1;j<=this->n;j++){
        cout<<this->res_arr->at(i)[j]<<endl;
      }
      cout<<endl;
    }
  }
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
int main() {
  int a;
  cin >> a;
  Nqueen* nqueen = new Nqueen(a);
  nqueen->BackTrack(1);
  nqueen->Print();
  return 0;
}
