#include <bits/stdc++.h>

#include "element.h"

/**
 * @brief 冒泡排序
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void bubble_sort(Element<T>* arr, int len) {
  if (len <= 1) return;
  bool switch_flag;
  int i, j;
  for (i = 0; i < len; i++) {
    //判断某一趟是否发生交换,如果未发生交换,显然已经有序,此时不需要再继续了
    switch_flag = false;
    for (j = 0; j < (len - i - 1); j++) {
      if (arr[j] > arr[j + 1]) {
        //发生交换
        auto temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
        switch_flag = true;
      }
    }
    if (switch_flag == false) return;
  }
}

/**
 * @brief 用于递归快排得到每次划分的位置
 * @tparam T
 * @param arr
 * @param left
 * @param right
 * @return int
 */
template <typename T>
int partition(Element<T>* arr, int left, int right) {
  Element<T> base = arr[left];
  while (left < right) {
    while (left < right && arr[right] >= base) --right;
    arr[left] = arr[right];
    while (left < right && arr[left] <= base) ++left;
    arr[right] = arr[left];
  }
  arr[left] = base;
  return left;
}

/**
 * @brief 快排_递归版
 * @param arr
 * @param low
 * @param high
 * @return
 */
template <typename T>
void quick_sort(Element<T>* arr, int low, int high) {
  //基准元素
  if (low < high) {
    int partition_val = partition(arr, low, high);
    //基准左边继续递归快排
    quick_sort(arr, low, partition_val - 1);
    //基准右边继续递归快排
    quick_sort(arr, partition_val + 1, high);
  }
  return;
}

int main() {
  Element<int>* arr =
      new Element<int>[10] { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
  //   bubble_sort(arr, 10);
  quick_sort(arr, 0, 9);
  for (int i = 0; i <= 9; i++) {
    cout << *(arr + i) << "\t";
  }
  return 0;
}