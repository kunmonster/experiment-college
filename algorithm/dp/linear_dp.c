#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int arr[41] = {0};

void compute()
{
    arr[0] =0; arr[1] = 1;
    for (int i = 2; i <= 40; i++)
    {
        arr[i] = arr[i - 2] + arr[i - 1];
    }
}

void climb()
{
    int M = 0;
    scanf("%d", &M);
    int i = 0;
    int input = 0;
    compute();
    while (i < M )
    {
        ++i;
        scanf("%d", &input);
        printf("%d\n", arr[input]);
    }

}

int main()
{
    climb();
}