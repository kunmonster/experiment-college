#include <bits/stdc++.h>
#include "element.h"
using namespace std;

/**
 * @brief 直接插入排序(升序)
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void stright_insert_sort(Element<T> *arr, int len) {
  if (len <= 1) return;
  // set the first element as the standard
  Element<T> guard;
  int j = 0;
  for (int i = 1; i < len; ++i) {
    if (*(arr + i) < *(arr + i - 1)) {
      //当前元素小于前一个元素
      guard = *(arr + i);
      for (j = (i - 1); (j >= 0) && (guard < arr[j]); --j) arr[j + 1] = arr[j];
      arr[j + 1] = guard;
    }
  }
}

/**
 * @brief  二分插入排序
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void binary_insert_sort(Element<T> *arr, int len) {
  if (len <= 1) return;
  //数组长度大于等于1

  Element<T> guard;
  int i, j;
  for (i = 1; i < len; ++i) {
    if (arr[i] < arr[i - 1]) {
      guard = arr[i];
      //得到插入的位置然后插入
      int low = 0, high = i - 1, mid = 0;
      while (low <= high) {
        mid = (low + high) / 2;
        if (guard < arr[mid])
          high = mid - 1;
        else
          low = mid + 1;
      }
      //插入位置为high+1
      //从i的前一个位置开始需要将插入位置开始的数都往后移
      for (j = (i - 1); j >= (high + 1); --j) arr[j + 1] = arr[j];
      arr[high + 1] = guard;
    }
  }
}

/**
 * @brief  希尔排序
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void shell_sort(Element<T> *arr, int len) {
  if (len <= 1) return;
  Element<T> guard;
  int dk, i, j;
  for (dk = len / 2; dk >= 1; dk /= 2) {
    for (i = dk; i < len; ++i) {
      if (arr[i] < arr[i - dk]) {
        guard = arr[i];
        for (j = i - dk; j >= 0 && arr[j] > guard; j -= dk)
          arr[j + dk] = arr[j];
        arr[j + dk] = guard;
      }
    }
  }
}

int main() {
  Element<int> *arr =
      new Element<int>[10] { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
  shell_sort(arr, 10);
  // binary_insert_sort(arr, 10);
  //   stright_insert_sort(arr, 10);
  for (int i = 0; i <= 9; i++) {
    cout << *(arr + i) << "\t";
  }
  return 0;
}