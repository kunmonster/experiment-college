/**
 * longest common subsequence
 * fkj
 * 2021.11.20
 **/
#include <time.h>

#include <iostream>

using namespace std;

void lcs_length(const int, const int, char *, char *, int **, int **);
void getSubSeq(const int, const int, char *, char *, int **, int **);
char *generate_str(int);

int main() {
  system("chcp 65001");
  cout << "输入序列a的长度:";
  int a_len;
  cin >> a_len;
  char *A = generate_str(a_len);
  cout << "输入序列B的长度:";
  int b_len;
  cin >> b_len;
  char *B = generate_str(b_len);
  int i;
  cout << "A序列为:";
  for (i = 0; i < a_len; i++) {
    cout << A[i] << " ";
  }
  cout << endl << "B序列为:";
  for (i = 0; i < b_len; i++) {
    cout << B[i] << " ";
  }
  int **c = new int *[a_len + 1];
  for (int i = 0; i < a_len + 1; i++) {
    c[i] = new int[b_len + 1];
  }
  int **pos = new int *[a_len];
  for (int i = 0; i < a_len; i++) {
    pos[i] = new int[b_len];
  }
  lcs_length(a_len, b_len, A, B, c, pos);
  char *res = new char[c[a_len][b_len]];
  getSubSeq(a_len, b_len, A, res, c, pos);
  cout << endl << "最长公共子序列为:";
  for (i = 0; i < c[a_len][b_len]; i++) {
    cout << res[i] << " ";
  }
  system("pause");
  return 0;
}

/**
 * paramters : sequence A , sequence B , longest length arr , position , length
 * of a, lenght of b
 */
void lcs_length(int len_a, int len_b, char *a, char *b, int **c, int **pos) {
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
      if (a[i - 1] == b[j - 1]) {
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
 *paramters : length of seq_a , length of seq_b , seq_a , sub_seq , cloeset
 *length arr , postion
 */
void getSubSeq(int len_a, int len_b, char *a, char *res, int **c, int **pos) {
  if (len_a == 0 || len_b == 0) return;
  if (c[len_a][len_b]) {
    if (pos[len_a - 1][len_b - 1] == 1) {
      res[c[len_a][len_b] - 1] = a[len_a - 1];
      getSubSeq(len_a - 1, len_b - 1, a, res, c, pos);
    } else if (pos[len_a - 1][len_b - 1] == 2) {
      getSubSeq(len_a - 1, len_b, a, res, c, pos);
    } else {
      getSubSeq(len_a, len_b - 1, a, res, c, pos);
    }
  }
}
char *generate_str(int len) {
  if (!len) return NULL;
  char *str = new char[len];
  int i;
  srand(time(0));
  for (i = 0; i < len; i++) {
    str[i] = (char)(rand() % 26 + 65);
  }
  return str;
}