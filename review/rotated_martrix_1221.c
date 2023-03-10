#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_matrix(int ***, int, int);
void input_matrix(int ***, int, int);
int **clockwise_90(int **, int, int);
int **counterClokWise_90(int **, int, int);
void symmetry_vertical(int ***, int, int);
void print_matrix(int **, int, int);
void swap(int *, int *);

int main() {
  int row = 0, col = 0, oper = 0;
  scanf("%d%d%d", &row, &col, &oper);
  int **matrix;
  init_matrix(&matrix, row, col);
  input_matrix(&matrix, row, col);
  int **res = clockwise_90(matrix, row, col);
  printf("顺时针90度:\n");
  print_matrix(res, col, row);
  printf("逆时针90度:\n");
  res = counterClokWise_90(res, col, row);
  print_matrix(res, row, col);
  symmetry_vertical(&res, row, col);
  printf("镜像对称:\n");
  print_matrix(res, row, col);

  return 0;
}

void init_matrix(int ***matrix, int row, int col) {
  (*matrix) = (int **)malloc(sizeof(int *) * row);
  if ((*matrix) == NULL) exit(-1);
  for (int i = 0; i < row; ++i) {
    *((*matrix) + i) = (int *)malloc(sizeof(int) * col);
    if (((*matrix) + i) == NULL) exit(-1);
    memset(*((*matrix) + i), 0, sizeof(int) * col);
  }
}

void input_matrix(int ***matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      scanf("%d", &(*matrix)[i][j]);
    }
  }
}

int **clockwise_90(int **matrix, int row, int col) {
  int **res = NULL;
  init_matrix(&res, col, row);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      res[j][row - i - 1] = matrix[i][j];
    }
  }
  return res;
}

int **counterClokWise_90(int **matrix, int row, int col) {
  int **res = NULL;
  init_matrix(&res, col, row);
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < row; j++) {
      res[i][j] = matrix[j][col - i - 1];
    }
  }
  return res;
}

void symmetry_vertical(int ***matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    int low = 0, high = col-1;
    while (low <= high) {
      swap(&(*matrix)[i][low++], &(*matrix)[i][high--]);
    }
  }
}

void print_matrix(int **matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (j == col - 1)
        printf("%d", matrix[i][j]);
      else
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}