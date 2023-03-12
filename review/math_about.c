#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 求最大公约数
int gcd(int, int);

// 最小公倍数
int lcm(int, int);

// 判断是不是素数
int is_prime(int);

// 埃氏筛
void ei_sift(int);

/// @brief 欧拉筛
/// @param int n 范围
void oula_sift(int);


int main() {
  // printf("%d", gcd(17, 8));
  ei_sift(100);
  return 0;
}

// 最大公约数
int gcd(int a, int b) {
  
  if (a % b == 0) return b;
  if (b == 1) return 1;
  return gcd(b, a % b);
}

// 最小公倍数
int lcm(int a, int b) { return a * b / gcd(a > b ? a : b, a <= b ? a : b); }

// 素数朴素判断
int is_prime(int a) {
  int mid = sqrt(a);
  for (int i = 2; i < mid; ++i) {
    if (a % i == 0) return 1;
  }
  return 1;
}

// 埃氏筛
void ei_sift(int n) {
  // 状态数组,1表示合数,0表示素数,初始化为素数
  int *isnprime = (int *)malloc(sizeof(int) * n);
  memset(isnprime, 0, n);
  // 0,1不是素数
  isnprime[0] = isnprime[1] = 1;
  for (int i = 2; i < sqrt(n); ++i) {
    if (isnprime[i] == 0) {
      for (int j = i * i; j < n; j += i) {
        isnprime[j] = 1;
      }
    }
  }
  for(int i =0;i<n;i++){
    if(isnprime[i] == 0) printf("%d ",i);
  }
  free(isnprime);
}
