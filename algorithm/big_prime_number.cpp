
#include <rand.h>

#include <iostream>

using namespace std;

typedef long long LL;

static Rand randnumber;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

/**
 * 快速乘法
 */
LL qucik_multiply(LL a, LL b) {
  //快速乘,转化为二进制,再相加
  LL ans = 0;
  while (b) {
    if (b & 1) {
      ans += a;
    }
    a += a;
    b >>= 1;
  }
  return ans;
}
/**
 * 快速幂
 *
 */
LL quick_power(LL a, LL b) {
  LL ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
    }
    b >>= 1;
    a *= a;
  }
  return ans;
}

bool Miller_Rabbin(LL n) {
  //判断是否为素数
  if (n == 2) return true;
  if (n < 2 || !(n & 1)) return false;
  LL m = n - 1;
  int k = 0;
  while ((m & 1) == 0) {
    k++;
    m >> 1;
  }
  for (int i = 0; i < 10; i++) {
    LL a = randnumber.generateRand(n - 1);
    LL x = quick_power(a, m);
    LL y = 0;
    for(int j=0;i<k;j++){
      y = qucik_multiply(x,x);
      if(y == 1 && x!=1 && x!=n-1) return false;
      x=y;
    }
    if(y!=1) return false;
  }
  return true;
}


int main() { return 0; }