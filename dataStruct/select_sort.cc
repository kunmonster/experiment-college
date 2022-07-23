/**
 * @file select_sort.cc
 * @author kkmonster
 * @brief
 * @version 0.1
 * @date 2022-07-13
 * @details 因为堆排序的时候有插入操作,所以在堆排序的时候使用vector
 *
 */

#include <bits/stdc++.h>

#include <vector>

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
 * @brief 根据关键字序列创建大根堆
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void create_max_heap(vector<Element<T>>& arr, int len) {
  if (len <= 1) return;
  //从最后一个子树开始调整
  int cur = (len - 1) / 2;
  while (cur >= 0) {
    adjust_max_heap(arr, cur, len);
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
void adjust_max_heap(vector<Element<T>>& arr, int root_index, int len) {
  Element<T> root = arr[root_index];
  for (int i = root_index * 2 + 1; i < len; i = i * 2 + 1) {
    //寻找直接子元素最大的,i是左子树的根,若i已经等于len-1了说明没有右子树,i已经在最后一个位置了
    if ((i < (len - 1)) && arr[i] < arr[i + 1]) ++i;
    //最大的都小于根关键字,此时结束寻找
    if (root >= arr[i])
      break;
    else {
      arr[root_index] = arr[i];
      //用较大的子关键字替换根位置的关键字,但是不能直接把根关键字放到该位置,因为可能破坏子树的大根堆结构
      //这时候需要继续在这个子树向下调整,最后找到放入根元素的位置
      root_index = i;
    }
  }
  arr[root_index] = root;
}

/**
 * @brief
 * 在大顶堆中加入新的元素
 * @tparam T
 * @param arr
 * @param len 当前堆的长度
 * @param element
 */
template <typename T>
void insert_element_in_max_heap(vector<Element<T>>& arr, int len,
                                Element<T>& element) {
  arr.push_back(element);
  create_max_heap(arr, len + 1);
}

/**
 * @brief
 * 堆排序,初始化堆,进行n趟的排序,每一趟先输出最大的元素,然后把最大的元素移到末尾,然后调整
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void head_sort(vector<Element<T>>& arr) {
  //建立初始堆
  int len = arr.size();
  create_min_heap(arr, len);
  //进行i-1趟,每一趟找到最大的元素,然后与最后一个元素交换(其实已经将最后一个元素earse了,这里我们使用索引限制)
  //再调整(自上而下,因为已经所有子树保持最大堆结构,只需向下寻找)
  for (int i = len - 1; i >= 0; --i) {
    auto temp = arr[0];
    cout << temp << "\t";
    swap(arr[i], arr[0]);
    adjust_min_heap(arr, 0, i);
  }
}

template <typename T>
void create_min_heap(vector<Element<T>>& _arr,int len) {
  if (len <= 1) return;
  int i = (len - 1) / 2;
  while (i >= 0) {
    adjust_min_heap(_arr, i,len);
    --i;
  }
}

template <typename T>
void adjust_min_heap(vector<Element<T>>& _arr, int root_index,int len) {

  Element<T> root = _arr[root_index];
  for (int i = 2 * root_index + 1; i < len; i = i * 2 + 1) {
    if ((i < len - 1) && (_arr[i] > _arr[i + 1])) ++i;
    if (_arr[root_index] <= _arr[i])
      break;
    else {
      _arr[root_index] = _arr[i];
      root_index = i;
    }
  }
  _arr[root_index] = root;
}

int main() {
  Element<int>* arr = new Element<int>[10] { 53, 17, 78, 9, 45, 65, 87, 32 };
  vector<Element<int>> vec_arr;
  for (int i = 0; i < 8; i++) {
    vec_arr.push_back(arr[i]);
  }
  create_min_heap(vec_arr,8);
  for (auto item : vec_arr) {
    cout << item << "\t";
  }
  cout<<endl;
  head_sort(vec_arr);
  // cout << endl;
  // Element<int> new_ele = {100};
  // insert_element_in_max_heap(vec_arr, 8, new_ele);

  // for (auto item : vec_arr) {
  //   cout << item << "\t";
  // }
  // head_sort(vec_arr);

  return 0;
}
