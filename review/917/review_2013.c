#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 素数筛选
int *eurla_sift(int);
int is_rec(int);
int is_prime(const int *, int);

int main()
{
    int *res = eurla_sift(10000);
    for (int i = 2; i <= 10000; i++)
    {
        if ((is_prime(res, i) == 1) && (is_rec(i) == 1))
            printf("%d ", i);
    }
}

int *eurla_sift(int n)
{
    int *res = (int *)malloc(sizeof(int) * (n + 1));
    memset(res, 0, sizeof(int) * (n + 1));

    // 从2开始判断
    for (int i = 2; i <= n; i++)
    {
        if (res[i] == 0)
        {
            // 将素数加入素数数组
            // 如果不是素数就直接遍历素数集合
            res[++res[0]] = i;
        }
        for (int j = 1; j <= res[0] && res[j] <= n / i; j++)
        {
            res[res[j] * i] = 1;
            if (i % res[j] == 0)
                break;
        }
    }
    return res;
}

int is_rec(int n)
{
    int bit_arr[5] = {0};
    int k = 0;
    while (n != 0)
    {
        bit_arr[k++] = n % 10;
        n /= 10;
    }
    k--;
    int i = 0;
    while (k >= i)
    {
        if (bit_arr[k--] != bit_arr[i++])
            return 0;
    }
    return 1;
}
int is_prime(const int *arr, int target)
{
    for (int i = 1; i < arr[0]; i++)
    {
        if (arr[i] == target)
            return 1;
    }
    return 0;
}