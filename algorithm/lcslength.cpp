/**
 * longest common subsequence
 * fkj
 * 2021.11.20
 **/
#include <iostream>
using namespace std;

void lcs_length(const int,const int,char *, char *, int **, int **);
void getSubSeq(const int, const int,char *, char *,int **, int **);

int main() {
  char a[] = {'0', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
  char b[] = {'0', 'B', 'D', 'C', 'A', 'B', 'A'};
  int **c = new int *[8];
  for (int i = 0; i < 8; i++) {
    c[i] = new int[7];
  }
  int **pos = new int *[7];
  for (int i = 0; i < 7; i++) {
    pos[i] = new int[6];
  }
  lcs_length(7, 6,a, b, c, pos );
  char *res = new char[c[7][6]];
  getSubSeq(7, 6, a, res, c, pos);
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
void lcs_length(int len_a, int len_b,char *a, char *b, int **c, int **pos) {
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
/**
*paramters : length of seq_a , length of seq_b , seq_a , sub_seq , cloeset length arr , postion
*/
void getSubSeq(int len_a, int len_b, char *a, char *res,int **c, int **pos) {
  if (len_a == 0 || len_b == 0) return;
  if (c[len_a][len_b]) {
    if (pos[len_a - 1][len_b - 1] == 1) {
      res[c[len_a][len_b] - 1] = a[len_a];
      getSubSeq(len_a - 1, len_b - 1, a, res,c, pos );
    } else if (pos[len_a - 1][len_b - 1] == 2) {
      getSubSeq( len_a - 1, len_b, a, res,c, pos);
    } else {
      getSubSeq(len_a, len_b - 1, a, res,c, pos );
    }
  }
}