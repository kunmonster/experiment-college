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
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (*(array + j) > *(array + j + 1)) {
        int temp = *(array + j + 1);
        *(array + j + 1) = *(array + j);
        *(array + j) = temp;
      }
    }
  }
}

// int main(int argc, char** argv) {
//   int array[] = {2, 9, 0, 7, 4};
//   int len = sizeof(array) / sizeof(int);
//   buddleSort(array, len);
//   for (int i = 0; i < len; i++) {
//     cout << array[i] << "\t";
//   }
//   return 0;
// }
