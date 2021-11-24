/**
 * longest common subsequence
 * fkj
 * 2021.11.20
 **/
#include <iostream>
using namespace std;

void lcs_length(char *, char *, int **, int **, int, int);
void getSubSeq(int **, int **, char *, char *, const int, const int);

int main() {
  char a[] = {'0', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
  char b[] = {'0', 'B', 'D', 'C', 'A', 'B', 'A'};
  int **c = new int *[8];
  for (int i = 0; i < 8; i++) {
    c[i] = new int[7];
  }
  int **pos = new int *[8];
  for (int i = 0; i < 8; i++) {
    pos[i] = new int[7];
  }
  lcs_length(a, b, c, pos, 7, 6);
  char *res = new char[c[7][6]];
  getSubSeq(c, pos, a, res, 7, 6);
  for (int i = 0; i < c[7][6]; i++) {
    cout << res[i] << " ";
  }
  system("pause");
  return 0;
}

/**
 * paramters : sequence A , sequence B , longest length arr , position , length
 * of a, lenght of b
 */
void lcs_length(char *a, char *b, int **c, int **pos, int len_a, int len_b) {
  if (!a && !b) {
    return;
  }
  int i, j;
  for (i = 1; i <= len_a; i++) {
    c[i][0] = 0;
  }
  for (j = 1; j <= len_b; j++) {
    c[0][j] = 0;
  }
  for (i = 1; i <= len_a; i++) {
    for (j = 1; j <= len_b; j++) {
      if (a[i] == b[j]) {
        c[i][j] = c[i - 1][j - 1] + 1;
        pos[i - 1][j - 1] = 1;
      } else if (c[i - 1][j] >= c[i][j - 1]) {
        c[i][j] = c[i - 1][j];
        pos[i - 1][j - 1] = 2;
      } else {
        c[i][j] = c[i][j - 1];
        pos[i - 1][j - 1] = 3;
      }
    }
  }
}
void getSubSeq(int **c, int **pos, char *a, char *res, int len_a, int len_b) {
  if (len_a == 0 || len_b == 0) return;
  if (c[len_a][len_b]) {
    if (pos[len_a - 1][len_b - 1] == 1) {
      res[c[len_a][len_b] - 1] = a[len_a - 1];
      getSubSeq(c, pos, a, res, len_a - 1, len_b - 1);
    } else if (pos[len_a - 1][len_b - 1] == 2) {
      getSubSeq(c, pos, a, res, len_a - 1, len_b);
    } else {
      getSubSeq(c, pos, a, res, len_a, len_b - 1);
    }
  }
}