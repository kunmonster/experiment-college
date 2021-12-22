#include <iomanip>
#include <iostream>

#include "./rand.h"

using namespace std;

class Dart {
 private:
  int n;         //投点个数
  double left;   //左边界限
  double right;  //右边界限
  Rand randNum;

 public:
  Dart(int n, double left, double right) {
    this->n = n;
    this->left = left;
    this->right = right;
    this->randNum = Rand();
  }
  double Dart_are(double (*f)(double x)) {
    int k = 0;
    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < n; i++) {
      x = this->randNum.generateRand_1();
      y = 1 * this->randNum.generateRand_1();
      if (y <= (*f)(x)) {
        k++;
      }
    }
    return 1 * (double)k / this->n;
  }
  double Dart_avg(double (*f)(double x)) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      //生成left-right之间的数
      double var_val = (right - left) * randNum.generateRand_1() + left;
      sum = sum + (*f)(var_val);
    }
    return (right - left) * sum / n;
  }
};

double f(double x) { return x * x; }

int main() {
  Dart dart100(100, 0, 1);
  Dart dart10000(10000, 0, 1);
  Dart dart1000000(1000000, 0, 1);
  Dart dart100000000(100000000, 0, 1);
  cout << "100个点:" << endl;
  cout << setprecision(10) << "随机投点:" << dart100.Dart_are(f) << endl;
  cout << setprecision(10) << "平均值:" << dart100.Dart_avg(f) << endl;
  cout << endl;
  cout << "10000个点:" << endl;
  cout << setprecision(10) << "随机投点:" << dart10000.Dart_are(f) << endl;
  cout << setprecision(10) << "平均值:" << dart10000.Dart_avg(f) << endl;
  cout << endl;
  cout << "1000000个点:" << endl;
  cout << setprecision(10) << "随机投点:" << dart1000000.Dart_are(f) << endl;
  cout << setprecision(10) << "平均值:" << dart1000000.Dart_avg(f) << endl;
  cout << endl;
  cout << "100000000个点:" << endl;
  cout << setprecision(10) << "随机投点:" << dart100000000.Dart_are(f) << endl;
  cout << setprecision(10) << "平均值:" << dart100000000.Dart_avg(f);
  return 0;
}