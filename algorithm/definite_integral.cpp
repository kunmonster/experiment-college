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
      y = this->randNum.generateRand_1();
      if ((*f)(x) <= y) {
        k++;
      }
    }
    return (double)k / this->n;
  }
  double Dart_avg(double (*f)(double x)) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      //生成left-right之间的数
      double var_val = (right - left) * randNum.generateRand_1() + left;
      sum += (*f)(var_val);
    }
    return (right - left) * sum / n;
  }
};

double f(double x) { return x * x; }

int main() {
  Dart dart(10000000, 0, 1);
  cout << dart.Dart_are(f) << endl;
  cout << dart.Dart_avg(f);
  return 0;
}