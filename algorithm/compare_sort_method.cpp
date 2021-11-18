#include <stdio.h>
#include <time.h>
#include <windows.h>
// #include <sys/time.h>
#include <iomanip>
#include <iostream>

#include "MergeSort.cpp"
#include "buddlesort.cpp"
#include "quicksort.cpp"

// #if define(LINUX)

using namespace std;

void buddleSort(int* array, const int len);
void Sort(int* arr, int* reg, int start, int end);
void quicksort(int*, int, int);

int* arraycp(int* origin, int len) {
  if (len) {
    int* res = new int[len];
    for (int i = 0; i < len; i++) {
      *(res + i) = *(origin + i);
    }
    return res;
  }
  return NULL;
}
int* generateArray(int num, int left, int right) {
  srand(time(0));
  int* arr = new int[num];
  for (int i = 0; i < num; i++) {
    *(arr + i) = rand() % (right - left + 1) + left;
  }
  return arr;
}

int main() {
  system("chcp 65001");
  std::cout << "please input the size of the array:";
  int num = 0;
  std::cin >> num;
  std::cout << "please input the range of the array element" << endl;
  int left = 0;
  int right = 0;
  std::cout << "left:";
  cin >> left;
  std::cout << "right:";
  cin >> right;
  int* arr = generateArray(num, left, right);
  int* arrcp1 = arraycp(arr, num);
  int* arrcp2 = arraycp(arr, num);
  int* reg = new int[num];
  // struct timeval start,end;
  LARGE_INTEGER t1, t2, tc;
  QueryPerformanceFrequency(&tc);

  double buddle_time, merge_time, quick_time;
  QueryPerformanceCounter(&t1);
  // // gettimeofday(&start,NULL);
  buddleSort(arr, num);
  QueryPerformanceCounter(&t2);
  buddle_time = (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart;

  // gettimeofday(&end,NULL);
  // buddle_time = (end.tv_sec-end.tv_sec)+(end.tv_usec - start.tv_usec) /
  // 1000000.0;

  QueryPerformanceFrequency(&tc);


  QueryPerformanceCounter(&t1);
  // gettimeofday(&start,NULL);

  quicksort(arrcp1, 0, num - 1);

  QueryPerformanceCounter(&t2);
  // gettimeofday(&end,NULL);

  quick_time = (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart;
  // quick_time = (end.tv_sec-end.tv_sec)+(end.tv_usec - start.tv_usec) /
  // 1000000.0;

  QueryPerformanceFrequency(&tc);

  QueryPerformanceCounter(&t1);
  // gettimeofday(&start,NULL);
  Sort(arrcp2, reg, 0, num - 1);

  QueryPerformanceCounter(&t2);
  // merge_time = (double)(end - start) / CLOCKS_PER_SEC;
  merge_time = (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart;
  // merge_time = (end.tv_sec-end.tv_sec)+(end.tv_usec - start.tv_usec) /
  // 1000000.0;

  cout << "冒泡:" << setprecision(15) << buddle_time << "秒" << endl;
  cout << "快排:" << setprecision(15) << quick_time << "秒" << endl;
  cout << "归并:" << setprecision(15) << merge_time << "秒" << endl;
  system("pause");
  return 0;
}