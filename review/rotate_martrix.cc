#include <stdio.h>
#include <stdlib.h>

#include <cstring>

void input_martrix(int ***, int);
void init_martrix(int ***, int);
void print_martrix(int **, int);
int check_rotate_degree(int **, int **, int);

int main() {
  int **origin;
  int **rotate;
  int n = 0;
  scanf("%d", &n);
  init_martrix(&origin, n);
  init_martrix(&rotate, n);
  input_martrix(&origin, n);
  input_martrix(&rotate, n);
//   //打印输出
//   print_martrix(origin, n);
//   print_martrix(rotate, n);
  int res = check_rotate_degree(origin, rotate, n);
  printf("%d", res);
  return 0;
}

void init_martrix(int ***martrix, int n) {
  int i = 0;
  *martrix = (int **)malloc(sizeof(int *) * n);
  if (*martrix == NULL) return;
  for (i = 0; i < n; i++) {
    (*martrix)[i] = (int *)malloc(sizeof(int) * n);
    if ((*martrix)[i] == NULL) return;
  }
}

void input_martrix(int ***martrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      //   printf("%d", &(*martrix)[i][j]);
      scanf("%d", &(*martrix)[i][j]);
      //   printf("%d", &martrix[i * n + j]);
    }
  }
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
int check_rotate_degree(int **origin, int **rotate, int n) {
  int res = -1;
  bool tag_1 = false;
  bool tag_2 = false;
  bool tag_3 = false;
  bool tag_4 = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (origin[i][j] != rotate[i][j]) {
        tag_1 = true;
      }
      if (origin[i][j] != rotate[j][n - i - 1]) {
        tag_2 = true;
      }
      if (origin[i][j] != rotate[n - i - 1][n - j - 1]) {
        tag_3 = true;
      }
      if (origin[i][j] != rotate[n - j - 1][i]) {
        tag_4 = true;
      }
    }
  }
  if (!tag_1) res = 0;
  if (!tag_2) res = 90;
  if (!tag_3) res = 180;
  if (!tag_4) res = 270;
  return res;
}
