/****
 * author : k
 * fun : buddle sort
 * date : 2021.10.8
 * */

#include <iostream>
using namespace std;

void buddleSort(int* array, const int len) {
  if (len == 0) {
    return;
  }
  int i,j,flag=0;
  for (i = 0; i < len - 1; i++) {
    for ( j = 0; j < len - 1 - i; j++) {
      if (*(array + j) > *(array + j + 1)) {
        flag=1;
        int temp = *(array + j + 1);
        *(array + j + 1) = *(array + j);
        *(array + j) = temp;
      }
    }
    if(!flag) break;
  }
}
