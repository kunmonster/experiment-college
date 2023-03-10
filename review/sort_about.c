#include <stdio.h>
#include <string.h>

void swap(int *, int *);
void print_arr(const int *, int);

// 直接插入排序
void straight_insert_sort(int *, int);
// 直接选择排序
void straight_select_sort(int *);
// 希尔排序
void shell_sort(int *);
// 快排
void quick_sort(int *);
// 二路归并
void bin_merge_sort(int *);

int main() {
  int arr[10] = {5, 6, 1, 3, 6, 7, 2, 7, 2, 7};
  printf("排序前:");
  print_arr(arr,10);
    printf("\n");

  straight_insert_sort(arr, 10);

  printf("排序后:");
  print_arr(arr,10);

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
