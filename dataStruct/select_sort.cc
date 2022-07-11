#include <bits/stdc++.h>

#include "element.h"
using namespace std;

/**
 * @brief 简单选择排序
 * @tparam T
 * @param arr 待排序的序列
 * @param len 待排序序列长度
 */
template <typename T>
void simple_select_sort(Element<T>* arr, int len) {
  if (len <= 1) return;
  Element<T> temp_val;
  int i, j, min;
  for (i = 0; i < len - 1; ++i) {
    min = i;
    for (j = i + 1; j < len; ++j) {
      min = arr[j] < arr[min] ? j : min;
    }
    swap(arr[min], arr[i]);
  }
}

/**
 * @brief Create a max heap object
 * 根据序列创建大根堆
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void create_max_heap(Element<T>* arr, int len) {
  if (len <= 1) return;
  int cur = len / 2 - 1;
  while (cur >= 0) {
    adjust_map_heap(arr, cur, len);
    --cur;
  }
}

/**
 * @brief 调整大根堆
 * 使用此函数时候,当前root_index为根的子树应已经满足大根堆的要求,这个要求也很好满足
 * 从最后一个子树开始执行这个算法即可,所以总体呈现自底向上,局部呈现自顶向下
 * @tparam T
 * @param arr
 * @param root_index 以root_index处元素为根的元素
 * @param len
 */
template <typename T>
void adjust_map_heap(Element<T>* arr, int root_index, int len) {
  Element<T> root = arr[root_index];
  for (int i = root_index * 2; i < len; i *= 2) {
    //寻找直接子元素最大的
    if (i < len - 1 && arr[i] < arr[i + 1]) ++i;
    //最大的都小于根关键字,此时结束寻找
    if (root >= arr[i])
      break;
    else {
      arr[root_index] = arr[i];
      //用较大的子关键字替换根位置的关键字,但是不能直接把根关键字放到改位置,因为可能破坏子树的大根堆结构
      //这时候需要继续在这个子树向下调整,最后找到放入根元素的位置
      root_index = i;
    }
  }
  arr[root_index] = root;
}

int main() {
  Element<int>* arr =
      new Element<int>[10] { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
  // simple_select_sort(arr, 10);
  create_max_heap(arr, 10);
  for (int i = 0; i <= 9; i++) {
    cout << *(arr + i) << "\t";
  }
  return 0;
}
