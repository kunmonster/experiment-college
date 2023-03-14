#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_start(int n)
{
	int sum = 0;
	for (int i = 1; i < n; i++)
		sum += i;
	return sum;
}

void print_triangle_withOneArr(int n)
{
	if (n == 0)
		return;
	int sum = (n % 2) == 0 ? (1 + n) * n / 2 : (1 + n) * n / 2 + (n / 2) + 1;

	int *p = (int *)malloc(sizeof(int) * (sum + 1));

	memset(p, 0, sizeof(int) * (sum + 1));

	p[0] = sum;
	p[1] = 1;

	// 层数标记,方便找到该层的起始和结束点
	int layer = 2;
	while (layer <= n)
	{
		// 将起始和结束点置为1,然后算中间
		int start = get_start(layer) + 1;
		int end = start + layer - 1;
		p[start] = 1;
		p[end] = 1;
		for (int i = start + 1; i < end; i++)
		{
			p[i] = p[i - layer] + p[i - layer + 1];
		}
		layer++;
	}
	int cur = 0;
	int sapce = 2 * n - 1;

	for (cur = 1; cur <= n; cur++)
	{
		int border = sapce - (cur + cur - 1) / 2;
		int i = 0;
		// 左边界
		for (i = 0; i < border; i++)
			printf(" ");
		// 右边界
		int start = get_start(cur) + 1;
		int end = start + cur - 1;
		for (i = start; i < end; i++)
			printf("%d ", p[i]);
		printf("%d", p[end]);
		for (i = 0; i < border; i++)
			printf(" ");
		printf("\n");
	}
}

int main()
{

	// int size = 0;

	// scanf("%d", &size);

	// if (size <= 20 && size > 0)
	// {

	// 	int **arr = (int **)malloc(sizeof(int *) * size);
	// 	int i = 0, j = 0;
	// 	for (i = 0; i < size; i++)
	// 	{
	// 		arr[i] = (int *)malloc(sizeof(int) * size);
	// 		memset(arr[i], 0, size * sizeof(int));
	// 	}

	// 	arr[0][0] = 1;
	// 	printf("%d \n", arr[0][0]);
	// 	for (i = 1; i < size; i++)
	// 	{
	// 		arr[i][0] = 1;
	// 		printf("%d ", arr[i][0]);
	// 		for (j = 1; j <= i; j++)
	// 		{
	// 			arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
	// 			if (i == j)
	// 				printf("%d", arr[i][j]);
	// 			else
	// 				printf("%d ", arr[i][j]);
	// 		}
	// 		printf("\n");
	// 	}
	// }
	print_triangle_withOneArr(6);

	return 0;
}
