#include <iostream>
using namespace std;
void quicksort(int *arr, int start, int end) {
  // exit
  if (!arr || start > end || start == end) {
    return;
  }
  int base = *(arr + start);
  int i = start;
  int j = end;
  while (i < j) {
    while ((i < j) && (*(arr + j)> base)) {
      j--;
    }
    *(arr + i) = *(arr + j);
    while ((i < j) && (*(arr + i) <= base)) {
      i++;
    }
    *(arr + j) = *(arr + i);
  }
  *(arr + i) = base;
  quicksort(arr, start, i - 1);
  quicksort(arr, i + 1, end);
}
