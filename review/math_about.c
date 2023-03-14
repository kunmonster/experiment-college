#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXN = 1000000 + 5;

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
int findGCD(int *, int);
int main()
{
  // printf("%d", gcd(17, 8));
  // ei_sift(100);
  int nums[] =
      {2, 5, 6, 9, 10};
  // oula_sift(100);
  printf("%d",findGCD(nums,5));
  return 0;
}

// 最大公约数
int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int findGCD(int *nums, int numsSize)
{
  if (numsSize == 1)
    return nums[0];
  int max = nums[0];
  int min = nums[0];
  for (int i = 1; i < numsSize; i++)
  {
    max = (max < nums[i] ? nums[i] : max);
    min = (min > nums[i] ? nums[i] : min);
  }
  return gcd(max, min);
}

// 最小公倍数
int lcm(int a, int b) { return a * b / gcd(a > b ? a : b, a <= b ? a : b); }

// 素数朴素判断
int is_prime(int a)
{
  int mid = sqrt(a);
  for (int i = 2; i < mid; ++i)
  {
    if (a % i == 0)
      return 1;
  }
  return 1;
}

// 埃氏筛
void ei_sift(int n)
{
  // 状态数组,1表示合数,0表示素数,初始化为素数
  int *isnprime = (int *)malloc(sizeof(int) * n);
  memset(isnprime, 0, sizeof(int) * n);
  // 0,1不是素数
  isnprime[0] = isnprime[1] = 1;
  for (int i = 2; i < sqrt(n); ++i)
  {
    if (isnprime[i] == 0)
    {
      for (int j = i * i; j < n; j += i)
      {
        isnprime[j] = 1;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (isnprime[i] == 0)
      printf("%d ", i);
  }
  free(isnprime);
  return;
}

/**
 * 欧拉筛选步骤
 * 1. 维护状态数组1表示是素数,0表示是合数,先将除0,1外的数置为素数
 * 2. i向后滑动,i是素数,将其加入素数集合,然后遍历素数集合,将素数集合中的i倍标记
 * 3.
 * 第二步标记过程中,如果i本身是合数,那么在遍历素数集合的死后,遍历一个元素就停止,因为欧拉筛要求是每个合数应该由其最小的素数因子,筛选出来
 * 如果i本身是合数的话,如果遍历素数集合的时候一直遍历,那么那个合数本身就可以拆分,此种方法筛选出来的合数还要被其他的数筛选
 * 4.
 * 重复上述过程,在筛选的过程中,需要注意,如果指定了某个范围以内的,那么在筛倍数的时候,需要注意范围,遍历素数集合时,乘积要小于范围才行,而且当超过范围一半时候,
 * 可以不用再筛选了,直接遍历判断素数了,因为去遍历素数集合从,2开始,必然要超过范围,此时判断合数没有意义
 *
 * */
void oula_sift(int n)
{
  // 素数状态集合,0表示素数
  int *prime = (int *)malloc(sizeof(int) * (n + 1));
  // 初始化全部标记为素数
  // memset是按字节赋值的,最好赋值成0
  memset(prime, 0, sizeof(int) * (n + 1));
  // 用prime[0]存当前素数的个数
  for (int i = 2; i <= n; i++)
  {
    // 当前数是素数,加入素数集合,如果不是素数下面直接遍历
    if (prime[i] == 0)
      prime[++prime[0]] = i;

    // 遍历素数集合
    for (int j = 1; j <= prime[0] && prime[j] * i <= n; ++j)
    {
      // 选合数
      prime[prime[j] * i] = 1;
      // 当i本身是合数,时候,只筛最小素数和其的乘积就行了,不然会出现重复筛选
      if (i % prime[j] == 0)
        break;
    }
  }
  printf("%d以内的素数有%d个:", n, prime[0]);
  for (int i = 1; i <= prime[0]; i++)
  {
    printf("%d ", prime[i]);
  }
  free(prime);
}