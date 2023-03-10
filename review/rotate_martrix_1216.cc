#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_martrix(int ***, int);
void print_martrix(int **, int);
int main() {
  int n = 0;
  scanf("%d", &n);
  if (n <= 0) exit(-1);
  int **martrix;
  generate_martrix(&martrix, n);
  print_martrix(martrix, n);
  return 0;
}
void print_martrix(int **martrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == n - 1)
        printf("%d", martrix[i][j]);
      else
        printf("%d ", martrix[i][j]);
    }
    printf("\n");
  }
}
void generate_martrix(int ***martrix, int n) {
  // 初始化
  (*martrix) = (int **)malloc(sizeof(int *) * n);
  if ((*martrix) == NULL) exit(-1);
  for (int i = 0; i < n; i++) {
    (*martrix)[i] = (int *)malloc(sizeof(int) * n);
    if ((*martrix)[i] == NULL) exit(-1);
    memset((*martrix)[i], 0, sizeof(int) * n);
  }
  //生成矩阵
  int count = 1;
  int bound = 1;
  int max = n * n;
  int i = 0, j = 0;
  while (count <= max) {
    while (i < n && (*martrix)[i][j] == 0) {
      (*martrix)[i++][j] = count;
      count++;
    }

    if (i == n) i = n - 1;
    while (j < n && (*martrix)[i][++j] == 0) {
      (*martrix)[i][j] = count++;
    }

    if (j == n) j = n - 1;

    while (i >= bound && (*martrix)[i - 1][j] == 0 && count <= max) {
      (*martrix)[--i][j] = count++;
    }

    while (j > bound && (*martrix)[i][j - 1] == 0 && count <= max) {
      (*martrix)[i][--j] = count++;
    }
    n--;
    i++;
    bound++;
  }
}
