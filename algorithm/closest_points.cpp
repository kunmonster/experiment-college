#include <math.h>
#include <string.h>

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

#define INFINITE 1e20
#define MAX_SIZE 10000

const double maxdis = 1e20;
typedef struct _POINT_ {
  /* data */
  double x;
  double y;
} point;

int middle_point[MAX_SIZE] = {0};

bool comp_x(point, point);
bool comp_y(point, point);
void sort_point_array(point *, int, int);
double dis(point, point);
double get_closest_dis(point *, int, int);
point *generate_points(int num);

int main() {
  system("chcp 65001");
  system("clear");
  cout << "请输入生成点的个数:";
  int num = 0;
  cin >> num;
  point *point_arr = generate_points(num);
  sort_point_array(point_arr, num, 0);
  double a = get_closest_dis(point_arr, 0, num - 1);
  std::cout << setprecision(8) << a << endl;
  system("pause");
  return 0;
}

bool comp_x(point p1, point p2) {
  //比较p1 < p2
  return p1.x <= p2.x ? true : false;
}

bool comp_y(point p1, point p2) { return p1.y <= p2.y ? true : false; }

void sort_point_array(point *point_array, int len, int mode) {
  //对所有点以x坐标为基准从小到大排序
  if (len == 0) return;
  int i, j, flag = 0;
  point temp;
  memset(&temp, 0, sizeof(temp));
  for (int i = 0; i < len; i++) {
    flag = 0;
    for (int j = 0; j < len - i - 1; j++) {
      if (mode == 0) {
        if (!comp_x(*(point_array + j), *(point_array + j + 1))) {
          flag = 1;
          temp = *(point_array + j);
          *(point_array + j) = *(point_array + j + 1);
          *(point_array + j + 1) = temp;
        }
      } else {
        if (!comp_y(*(point_array + j), *(point_array + j + 1))) {
          flag = 1;
          temp = *(point_array + j);
          *(point_array + j) = *(point_array + j + 1);
          *(point_array + j + 1) = temp;
        }
      }
    }
    if (!flag) {
      break;
    }
  }
}

double dis(point a, point b) {
  //计算两点之间的距离
  return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0));
}

double get_closest_dis(point *point_array, int left, int right) {
  //获取最短距离
  double distance = maxdis;
  if (left == right) {
    return distance;
  }
  if ((left + 1) == right) {
    return dis(*(point_array + left), *(point_array + right));
  }
  int m = (right + left) / 2;
  double left_dis = get_closest_dis(point_array, left, m);
  double right_dis = get_closest_dis(point_array, m + 1, right);

  double min = left_dis < right_dis ? left_dis : right_dis;

  int i, j, k = 0;
  for (i = left; i <= right; i++) {
    if (fabs(((*(point_array + i)).x - (*(point_array + m)).x)) < min) {
      // fabs()获取浮点数的绝对值
      //将中间的点存入该数组
      ::middle_point[k++] = i;
    }
  }
  //按纵坐标升序排列
  sort_point_array(point_array, right - right + 1, 1);
  //这里可以不用加绝对值
  for (i = 0; i < k; i++) {
    for (j = i + 1; j < k && fabs((*(point_array + middle_point[j])).y -
                                  (*(point_array + middle_point[i])).y) < min;
         j++) {
      double middle_dis = dis(*(point_array + middle_point[i]),
                              *(point_array + middle_point[j]));
      if (middle_dis < min) min = middle_dis;
    }
  }
  return min;
}
point *generate_points(int num) {
  if (num) {
    point *point_array = new point[num];
    srand(time(0));
    for (int i = 0; i < num; i++) {
      //设置种子
      (*(point_array + i)).x = (double)(rand()) / RAND_MAX;
      (*(point_array + i)).y = (double)(rand()) / RAND_MAX;
    }
    cout << "所有点对" << endl;
    for (int j = 0; j < num; j++) {
      //所有点对
      cout << "(" << (*(point_array + j)).x << "," << (*(point_array + j)).y
           << ")" << endl;
    }
    return point_array;
  }
  return NULL;
}