
#include <iostream>

#include "./rand.h"

using namespace std;

typedef long long LL;

static Rand randnumber;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

/**
 * 快速乘法
 */
LL qucik_multiply(LL a, LL b, LL p) {
  //快速乘,转化为二进制,再相加,对P求余
  LL ans = 0;
  while (b) {
    if (b & 1) {
      ans = (ans + a) % p;
    }
    b >>= 1;
    a = (a + a) % p;
  }
  return ans;
}
/**
 * 快速幂,并且对P求余数
 */
LL quick_power(LL a, LL b, LL p) {
  LL ans = 1;
  while (b) {
    if (b & 1) {
      ans = (ans * a) % p;
    }
    b >>= 1;
    a = (a * a) % p;
  }
  return ans;
}

bool Miller_Rabin(LL n) {
  //判断是否为素数
  if (n == 2) return true;
  if (n < 2 || n % 2 == 0) return false;
  LL m = n - 1;
  int k = 0;
  //找到公式中的K然后开始从k*2^0开始探测
  while ((m & 1) == 0) {
    k++;      //为t
    m >>= 1;  //为k
  }
  //费马小定律
  // a^p-1 = 1(mod p)
  // 10为产生的a的个数
  for (int i = 0; i < 10; i++) {
    LL a = randnumber.generateRand(n - 2) + 1;
    //将a进行快速幂操作,幂为m(公式中的k)
    cout << "选定区间内的随机数a为:" << a << endl;
    LL x = quick_power(a, m, n);
    LL y = 0;
    for (int j = 0; j < k; j++) {
      //从a^m开始探测,每一次探测将其平方,注意使用的取模运算法则
      cout << "探测次数即a^(k*2^j) j=" << j << endl;
      y = qucik_multiply(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) return false;
      x = y;
    }
    if (y != 1) return false;
    cout << endl << "i=" << i << endl;
  }
  return true;
}

int main() {
  LL n;
  while (cin >> n) {
    if (Miller_Rabin(n))
      cout << n << "是素数" << endl;
    else
      cout << n << "不是素数" << endl;
  }
  return 0;
  return 0;
}