# 格式类题目

1. 杨辉三角
    - 题目描述


2. 旋转矩阵(判断两个矩阵是不是具有旋转关系)
    - 题目描述: 输入矩阵阶数，然后连续输入两个矩阵,判断第二个矩阵是不是第一个矩阵通过0,90,180,270度旋转得到的,是就返回度数，否则返回-1
    - 思路
      * 分析旋转各个度数的行列的关系
        1. 旋转0度,直接判断origin\[i][j] != rotated\[i][j] 满足显然就是不是旋转0度得到的
        2. 旋转90度
         - origin
          
            | 1 | 2 | 3 |
            | :-: | :-: | :-:|
            | 4 | 5 | 6 |
            | 7 | 8 | 9 |

         - rotated
            
            | 7 | 4 | 1 |
            | :-: | :-: | :-:|
            | 8 | 5 | 2 |
            | 9 | 6 | 3 |

         + 可以看出,第i行跑到了倒数第i列
         + 第j列转到了,第j行
         + 所以只需判断origin\[i][j]与rotated\[j][n-i-1]
        1. 旋转180度,同上，要么连续旋转两个90度,要么寻找索引关系    
    - 题解
    
``` C
//矩阵输入函数
void input_martrix(int ***, int);
//分配内存并初始化
void init_martrix(int ***, int);
//输出矩阵
void print_martrix(int **, int);
//查看矩阵旋转的度数
int check_rotate_degree(int **, int **, int);

int main() {
  int **origin;
  int **rotate;
  int n = 0;
  scanf("%d", &n);
  init_martrix(&origin, n);
  init_martrix(&rotate, n);
  input_martrix(&origin, n);
  input_martrix(&rotate, n);
//   //打印输出
//   print_martrix(origin, n);
//   print_martrix(rotate, n);
  int res = check_rotate_degree(origin, rotate, n);
  printf("%d", res);
  return 0;
}

//用三级指针,是因为传二级指针会拷贝一个二级指针,并不能初始化二级指针本身
void init_martrix(int ***martrix, int n) {
  int i = 0;
  *martrix = (int **)malloc(sizeof(int *) * n);
  if (*martrix == NULL) return;
  for (i = 0; i < n; i++) {
    (*martrix)[i] = (int *)malloc(sizeof(int) * n);
    if ((*martrix)[i] == NULL) return;
    //还要来个初始化memset
  }
}

void input_martrix(int ***martrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &(*martrix)[i][j]);
    }
  }
}

void print_martrix(int **martrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == n - 1)
        printf("%d", martrix[i][j]);
      else
        printf("%d ", martrix[i][j]);
    }
    printf("\n");
  }
}
int check_rotate_degree(int **origin, int **rotate, int n) {
   //用于判断旋转多少度,有个小技巧,用标记,只要不满足旋转度数就打标记,最后就能快速得出旋转的度数,但是当矩阵本来就是对称的时候,输出的度数可能与打标记的顺序有关
  int res = -1;
  bool tag_1 = false;
  bool tag_2 = false;
  bool tag_3 = false;
  bool tag_4 = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (origin[i][j] != rotate[i][j]) {
        tag_1 = true;
      }
      if (origin[i][j] != rotate[j][n - i - 1]) {
        tag_2 = true;
      }
      if (origin[i][j] != rotate[n - i - 1][n - j - 1]) {
        tag_3 = true;
      }
      if (origin[i][j] != rotate[n - j - 1][i]) {
        tag_4 = true;
      }
    }
  }
  if (!tag_1) res = 0;
  if (!tag_2) res = 90;
  if (!tag_3) res = 180;
  if (!tag_4) res = 270;
  return res;
}
```

1. 旋转方阵(1216)
   - 描述:从(0,0)开始逆时针旋转生成矩阵,填充数字从1开始
   - 示例:输入矩阵阶数3
   - 输出
     
     | 1 | 8 | 7 |
     | :-: | :-: | :-: |
     | 2 | 9 | 6 |
     | 3 | 4 | 5 |
   
   - 思路:
      1. 给矩阵分配内存并初始化全部为0
      2. 维护一个填充的数字计数器和一个层数计数器
      3. 从(0,0)开始往下搜索,为0且未到边界就填充
      4. 到底部就开始向右搜索,为0且未到边界,填充
      5. 再向上填充,为0且未到边界(这里要注意遍历层数)
      6. 向左填充,为0且未到边界
      7. 遍历完将行计数器加1,然后继续第三步,起点改变
   - 代码
``` C
   void generate_martrix(int ***martrix, int n) {
  // 初始化
  (*martrix) = (int **)malloc(sizeof(int *) * n);
  if ((*martrix) == NULL) exit(-1);
  for (int i = 0; i < n; i++) {
    (*martrix)[i] = (int *)malloc(sizeof(int) * n);
    if ((*martrix)[i] == NULL) exit(-1);
    memset((*martrix)[i], 0, sizeof(int) * n);
  }
  //生成矩阵
  //填充数字计数器
  int count = 1;
  //层数计数器
  int bound = 1;
  //最大数字
  int max = n * n;
  //行列索引
  int i = 0, j = 0;
  while (count <= max) {
   //向下搜索
    while (i < n && (*martrix)[i][j] == 0) {
      (*martrix)[i++][j] = count;
      count++;
    }

   //到达底部,向右搜索
    if (i == n) i = n - 1;
    while (j < n && (*martrix)[i][++j] == 0) {
      (*martrix)[i][j] = count++;
    }

   //到达有边界,向上搜索
    if (j == n) j = n - 1;

    while (i >= bound && (*martrix)[i - 1][j] == 0 && count <= max) {
      (*martrix)[--i][j] = count++;
    }

   //向左搜索
    while (j > bound && (*martrix)[i][j - 1] == 0 && count <= max) {
      (*martrix)[i][--j] = count++;
    }
    //将边界缩小一圈
    n--;
    //行计数器往下移动
    i++;
    //遍历层数加一
    bound++;
  }
  }
``` 