#include <bits/stdc++.h>

using namespace std;

void Jsutify(int a, int b, int c) {
  cout << "路径覆盖a";
  if (a > 0 && a < 200 && b > 0 && b < 200 && c > 0 && c < 200) {
    // cout << "T1 T2 T3 " << endl;
    cout << "->c" << endl;
    if (a < b + c && b < a + c && c < a + b) {
      cout << "->e";
      // cout << "T4 T5 T6" << endl;
      if (a == b && b == c) {
        cout << "->f";
        // cout << "T7  T8" << endl;
        // cout << "条件2真条件3真" << endl;
        cout << "->j" << endl;
        cout << "这三条边构成等边三角形" << endl;

      } else {
        cout << "->g";
        // if (a == b) {
        //   cout << "T7  F8";
        // } else if (b == c)
        //   cout << "F7 T8" << endl;
        // else
        //   cout << "F7 F8" << endl;
        if (pow(a, 2) + pow(b, 2) == pow(c, 2) ||
            pow(c, 2) + pow(b, 2) == pow(a, 2) ||
            pow(a, 2) + pow(c, 2) == pow(b, 2)) {
          // cout << "条件3假条件4真" << endl;
          // if (pow(a, 2) + pow(b, 2) == pow(c, 2)) {
          //   cout << "T9  ";
          // } else
          //   cout << "F9" << endl;
          // if (pow(b, 2) + pow(c, 2) == pow(a, 2)) {
          //   cout << "T10  ";
          // } else
          //   cout << "F10" << endl;
          // if (pow(a, 2) + pow(c, 2) == pow(b, 2)) {
          //   cout << "T11  ";
          // } else
          //   cout << "F11" << endl;
          cout << "->h";
          cout << "->j" << endl;
          cout << "这三条边组成直角三角形" << endl;
          return;
        } else {
          // cout << "条件4假" << endl;
          cout << "->i";
          cout << "->j" << endl;
          cout << "这三条边组成一般三角形" << endl;
        }
      }
    } else {
      // if (a < b + c) {
      //   cout << "T4  ";
      // } else {
      //   cout << "F4" << endl;
      // }
      // if (b < a + c) {
      //   cout << "T5  ";
      // } else {
      //   cout << "F5" << endl;
      // }
      // if (c < a + b) {
      //   cout << "T6  ";
      // } else {
      //   cout << "F6" << endl;
      // }
      // cout << "条件1真条件2假" << endl;
      cout << "->d";
      cout << "->j" << endl;
      cout << "非三角形" << endl;
    }
  } else {
    // if (a > 0 && a < 200) {
    //   cout << "T1  ";
    // } else
    //   cout << "F1" << endl;
    // if (b > 0 && b < 200) {
    //   cout << "T2  ";
    // } else
    //   cout << "F2" << endl;
    // if (c > 0 && c < 200) {
    //   cout << "T3  ";
    // } else
    //   cout << "F3" << endl;
    cout << "->b";
    // cout << "条件1为假" << endl;
    cout << "->j" << endl;
    cout << "边的取值不符合要求" << endl;
  }
  return;
}

int main() {
  int a, b, c;
  while (true) {
    cin >> a >> b >> c;
    Jsutify(a, b, c);
  }
  return 0;
}