/**
 * fkj
 * 214.get the max k num
 * 2022.1.7
 */
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <vector>

using namespace std;

//快排
void quick_sort(vector<int>& arr, int left, int right) {
  if (left >= right) return;
  srand(time(0));
  int index = rand() % (right - left + 1) + left;
  int base = arr[index];
  int i = left, j = right;
  int temp;
  temp = arr[index];
  arr[index] = arr[i];
  arr[i] = temp;
  while (i < j) {
    while (i < j && arr[j] > base) {
      j--;
    }
    arr[i] = arr[j];
    while (i < j && arr[i] <= base) {
      i++;
    }
    arr[j] = arr[i];
  }
  arr[i] = base;
  quick_sort(arr, left, i - 1);
  quick_sort(arr, j + 1, right);
}

int main() {
  vector<int> arr{3, 2, 1, 5, 6, 4,-1,4,7,10,9};
  quick_sort(arr, 0, 10);
  return 0;
}