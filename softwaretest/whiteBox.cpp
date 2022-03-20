#include <bits/stdc++.h>
using namespace std;

void testWB() {
  int x, y, z;
  cout << "按次序输入x,y" << endl;
  cin >> x >> y;
  cout << "覆盖路径:";
  cout << "a->";
  if (x > 0 && y > 0) {
    cout << "b->";
    z = x + y + 10;
  } else {
    cout << "c->";
    z = x + y - 10;
  }
  if (z < 0) {
    cout << "d->";
    z = 0;

  } else
    cout << "e->";
  cout << "f";
  cout << endl << "z:" << z << endl;
}

int confirm(int a, int b, int c) {
  if ((a + b > c) && (a + c > b) && (b + c > a)) {
    //判断为三角形
    if ((a == b) && (b == c)) return 3;              //等边三角形
    if ((a == b) || (b == c) || (a == c)) return 2;  //等腰三角形
    return 1;                                        //普通三角形
  }
  //非三角形
  return 0;
}
void showResult(int parm) {
  switch (parm) {
    case 0:
      cout << "这不是一个三角形" << endl;
      break;
    case 1:
      cout << "这是一个普通三角形" << endl;
      break;
    case 2:
      cout << "这是一个等腰三角形" << endl;
      break;
    case 3:
      cout << "这是一个等边三角形" << endl;
      break;
    default:
      break;
  }
}

int main() {
  // while (1) {
  //   testWB();
  // }
  while (true) {
    int a, b, c;
    cout << "请输入三条边的值:";
    cin.clear();
    cin >>a>>b>>c;
    showResult(confirm(a, b, c));
  }
  return 0;
}