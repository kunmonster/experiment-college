#include <stdio.h>
#include <stdlib.h>

// 从文件读取数字,然后计算最大公约数,写入文件
void compute_gcd_and_write();
int gcd(int, int);
int lcm(int, int);
int max(int, int);
int min(int, int);

int main()
{
    compute_gcd_and_write();
    return 0;
}

void compute_gcd_and_write()
{
    FILE *file_in,* file_out;
    if ((file_in = fopen("D:\\vscode\\c++Gitrepo\\review\\917\\number.ini", "r")) == NULL)
    {
        fputs("文件打开失败", stdout);
        exit(2);
    }
        if ((file_out = fopen("D:\\vscode\\c++Gitrepo\\review\\917\\number.out", "w+")) == NULL)
    {
        fputs("文件打开失败", stdout);
        exit(2);
    }
    int a , b;
    int gcd_val;
    int lcm_val;

    

    while (!feof(file_in))
    {
        fscanf(file_in,"%d%d", &a, &b);
        gcd_val = gcd(max(a, b), min(a, b));
        lcm_val = (a*b) / gcd_val;
        fprintf(file_out,"%d %d\n" , gcd_val,lcm_val);
    }
    fclose(file_in);
    fclose(file_out);
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a * b / gcd(a < b ? b : a, a > b ? b : a);
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}