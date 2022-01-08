/**
 *fkj
 * 40.剑指offer.求出最小的K个数，实际上就是排序，由这个题来实现各种排序算法
 * 2022.1.8
 */
#include <stdlib.h>

#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int> &arr, int left, int right) {
  if (left >= right) return;
  int i = left;
  int j = right;
  int index = rand() % (right - left + 1) + left;
  int base = arr[index];
  //将基准元素换到第一个元素去,变成普通快排
  int temp = arr[i];
  arr[i] = base;
  arr[index] = temp;
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
  quick_sort(arr,left,i-1);
  quick_sort(arr,i+1,right);
}

int main() { return 0; }