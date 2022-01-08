/**
 * fkj
 * 堆排序
 * 2022.1.8
 */
#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b) {
  int temp = a;
  b = a;
  a = temp;
}

int max(int a, int b) { return a <= b ? b : a; }

void creat_head(vector<int> &arr) {
  int size = arr.size();
  int root = 0;
  int i = 0;
  while (i < size) {
    if (arr[i] < arr[2 * i]) {
      swap(arr[i], arr[2 * i]);
    }
    if (arr[i] < arr[2 * i + 1]) {
      swap(arr[i], arr[2 * i + 1]);
    }
  }
}
int main() { return 0; }