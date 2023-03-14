#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//大数加法
char *bigDecimalAdd(char *, char *);



int main()
{

    char a[101];
    char b[101];
    printf("请输入两个不超过100位的大数,以空格或者回车分隔\n");
    scanf("%s%s", a, b);

    char *res = bigDecimalAdd(a, b);
    printf("\n");
    printf("result:%s", res);

    return 0;
}


//大数加法
char *bigDecimalAdd(char *a, char *b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);

    // 获取较长的len
    int len = len_a < len_b ? len_b : len_a;

    char *res = (char *)malloc(sizeof(char) * (len + 2));

    memset(res, 0, sizeof(char) * (len + 2));
    int i = len_a - 1, j = len_b - 1;
    int c = 0;
    int k = len + 1;
    int sum = 0;
    res[k] = '\0';
    k--;
    while (i >= 0 && j >= 0 && k >= 0)
    {
        sum = (a[i--] - '0') + (b[j--] - '0') + c;
        res[k--] = (sum % 10) + '0';
        c = sum / 10;
    }
    while (i >= 0 && k >= 0)
    {
        sum = (a[i--] - '0') + c;
        res[k--] = (sum % 10) + '0';
        c = sum / 10;
    }
    while (j >= 0 && k >= 0)
    {

        sum = (b[j--] - '0') + c;
        res[k--] = (sum % 10) + '0';
        c = sum / 10;
    }
    if (k >= 0 && c > 0)
        res[k--] = c + '0';
    else
    {
        res = res + 1;
    }
    return res;
}
