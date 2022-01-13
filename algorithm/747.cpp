/**
 * fkj
 * 2022.1.13
 * 747
 *
 */
#include <iostream>
#include <vector>

using namespace std;

int getindex(vector<int>& arr) {
  int len = arr.size();
  int max = 0;
  int second;
  int index;
  //数组只有一个数的情况
  if (len == 0) return 0;
  for (int i = 0; i < len; i++) {
    if (arr[i] > max) {
      second = max;
      max = arr[i];
      index = i;
    } else if (second < arr[i]) {
      second = arr[i];
    }
  }
  return (max / 2) >= second ? index : -1;
}

int main() {
  vector<int> arr(5);
  int i = 0;
  while (i < 5) {
    cin >> arr[i];
    i++;
  }
  int index = getindex(arr);
  cout << endl << index;

  return 0;
}