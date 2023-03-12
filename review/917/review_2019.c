/***
 * 重庆大学2019年c语言机试真题
 */

#include <stdio.h>
#include <stdlib.h>

// 二分查找最小值
int findMin(const int *, int, int);
// 计算n条直线可以将1个平面分成多少个子平面
int get_plane(int);

// 从升序数组中查找M的位置，如果不存在M直接返回比M小的最大的数的索引
int get_M_index(const int *, int, int);

void print_arr(const int *, int size);

int main() {
  int arr[20] = {5, 6, 1,  3,  6, 7,  2,  7, 2,  7,
                 9, 4, 10, -1, 1, 12, 15, 3, 16, 10};

  int array[5] = {1, 3, 15, 70, 108};

  printf("索引位于:%d", get_M_index(array, 20, 5));
  //   printf("最小值为:%d", findMin(arr, 0, 19));
  return 0;
}

// 二分找最小值
int findMin(const int *arr, int low, int high) {
  if (low == high) return arr[low];
  int mid = (high - low) / 2 + low;
  int l = findMin(arr, low, mid);
  int r = findMin(arr, mid + 1, high);
  return l <= r ? l : r;
}
void print_arr(const int *arr, int size) {
  for (int i = 0; i < size; i++)

  {
    i == (size - 1) ? printf("%d", arr[i]) : printf("%d ", arr[i]);
  }
}
int get_M_index(const int *arr, int M, int size) {
  int low = 0;
  int high = size - 1;
  int mid = 0;
  while (low < high) {
    mid = (high - low) / 2 + low;
    if (arr[mid] == M)
      return mid;
    else if (arr[mid] > M) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
    
  }
  return low - 1;
}
