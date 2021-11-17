#include <cstdlib>
#include <ctime>
#include <iostream>

#include "MergeSort.cpp"
#include "buddlesort.cpp"
#include "quicksort.cpp"

using namespace std;

void buddleSort(int* array, const int len);
void Sort(int* arr, int* reg, int start, int end);
void quicksort(int*, int, int);

int* arraycp(int * origin, int len) {
  if (len) {
    int* res = new int[len];
    for (int i = 0; i < len; i++) {
      *(res+i) = *(origin+i);
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
  std::cout << "please input the size of the array:";
  int num = 0;
  std::cin >> num;
  std::cout << "please input the range of the array element" << endl;
  int left = 0;
  int right = 0;
  std::cout << "left:";
  cin >> left;
  std::cout << endl << "right:";
  cin >> right;
  int* arr = generateArray(num, left, right);
  int * arrcp1 = arraycp(arr,num);
  int * arrcp2 = arraycp(arr,num);
  int * reg = new int[num];
  clock_t start, end;
  double buddle_time, merge_time, quick_time;
  start = clock();
  buddleSort(arr, num);
  end = clock();
  buddle_time = (double)(end - start) / CLOCKS_PER_SEC;

  start = clock();
  quicksort(arrcp1,0,num-1);
  end = clock();
  quick_time = (double)(end-start) / CLOCKS_PER_SEC;
    
  start = clock();
  Sort(arrcp2,reg,0,num-1);
  end = clock();
  merge_time = (double)(end-start) / CLOCKS_PER_SEC;
  
  cout <<"冒泡:"<<buddle_time<<endl<<"快排:"<<quick_time<<endl<<"归并:"<<merge_time<<endl;
  system("pause");
  return 0;
}