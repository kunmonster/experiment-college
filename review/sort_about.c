#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void swap(int *, int *);
void print_arr(const int *, int);

// 直接插入排序
void straight_insert_sort(int *, int);
// 直接选择排序
void straight_select_sort(int *, int);
// 希尔排序
void shell_sort(int *, int);

// 递归快排位置划分
int partion(int *, int, int);

// 快排
void quick_sort(int *, int, int);
// 二路归并
void bin_merge_sort(int *, int *, int, int);
//堆排序
void heap_sort();


int main() {
  int arr[20] = {5, 6, 1,  3, 6, 7,  2,  7, 2,  7,
                 9, 4, 10, 2, 1, 12, 15, 3, 16, 10};
  printf("排序前:");
  print_arr(arr, 20);
  printf("\n");
  int tmp_arr[20];

  // straight_insert_sort(arr, 10);
  // straight_select_sort(arr, 10);
  // shell_sort(arr, 20);
  // quick_sort(arr, 0, 19);
  bin_merge_sort(arr, tmp_arr, 0, 19);
  printf("排序后:");
  print_arr(arr, 20);

  return 0;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void print_arr(const int *arr, int size) {
  for (int i = 0; i < size; i++)

  {
    i == (size - 1) ? printf("%d", arr[i]) : printf("%d ", arr[i]);
  }
}



// 直接插入
void straight_insert_sort(int *arr, int size) {
  for (int i = 1; i < size; i++) {
    if (arr[i - 1] > arr[i]) {
      // 在前面去找插入的地方
      int base = arr[i];
      for (int j = (i - 1); j >= 0; --j) {
        if (arr[j] <= base) break;
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

// 直接选择
void straight_select_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    int replace = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[replace]) replace = j;
    }
    swap(&arr[replace], &arr[i]);
  }
}

// 希尔排序
void shell_sort(int *arr, int size) {
  int dx = size / 2;
  while (dx >= 1) {
    for (int i = dx; i < size; i += dx) {
      if (arr[i] < arr[i - dx]) {
        // 组内相邻需要替换
        int base = arr[i];
        for (int j = (i - dx); j >= 0; j -= dx) {
          if (arr[j] <= base) break;
          swap(&arr[j], &arr[j + dx]);
        }
      }
    }
    dx >>= 1;
  }
}

// 快排位置划分
int partion(int *arr, int left, int right) {
  int base = arr[left];
  while (left < right) {
    while (arr[right] >= base && right > left) --right;
    arr[left] = arr[right];
    while (arr[left] <= base && left < right) ++left;
    arr[right] = arr[left];
  }
  arr[left] = base;

  return left;
}

// 快排,递归版本
void quick_sort(int *arr, int low, int high) {
  if (low >= high) return;
  int pos = partion(arr, low, high);
  quick_sort(arr, low, pos - 1);
  quick_sort(arr, pos + 1, high);
}

void bin_merge_sort(int *arr, int *tmp, int low, int high) {
  if (low >= high) return;
  int mid = (high - low) / 2 + low;
  bin_merge_sort(arr, tmp, low, mid);
  bin_merge_sort(arr, tmp, mid + 1, high);
  // 合并
  int l = low;
  int r = mid + 1;
  int cur = low;
  // 新开数组
  while (l <= mid && r <= high) {
    tmp[cur++] = (arr[l] <= arr[r] ? arr[l++] : arr[r++]);
  }
  while (l <= mid) {
    tmp[cur++] = arr[l++];
  }
  while (r <= high) tmp[cur++] = arr[r++];

  for (cur = low; cur <= high; cur++) {
    arr[cur] = tmp[cur];
  }
}