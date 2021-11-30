#include <iostream>
using namespace std;

#define MAX_INT 2147483648

void dijstra(int, int, int *, int *, int **);

int main() { return 0; }

/**
 *dijstra 单源最短路径
 *point_num
 */
void dijstra(int point_num, int start, int *dis, int *pre, int **g) {
  if (!point_num) return;
  //维护一个标记数组，记录第n个点是否在特殊路径集合中
  bool s[point_num] = {false};
  int i, j;
  s[start - 1] = true;
  dis[start - 1] = 0;
  for (i = 0; i < point_num; i++) {
    dis[i] = g[start - 1][i];
    if (dis[i] == MAX_INT) {
      //没有直接相连的路径
      pre[i] = -1;
    } else
      pre[i] = start - 1;
  }

  //选择最短路径节点,并更新dis
  for (i = 0; i < point_num; i++) {
    int temp = MAX_INT;
    int min_point = start - 1;
    for (j = 0; j < point_num; j++) {
      if (!s[j] && dis[j] < temp) {
        min_point = j;
        temp = dis[j];
      }
    }
    s[min_point] = true;

    //更新dis
    for (j = 0; j < point_num; j++) {
      if ((!s[j]) && (g[min_point][j] < MAX_INT)) {
        int update_dis = g[min_point][i] + dis[j];
        if (update_dis < dis[j]) {
          dis[i] = update_dis;
          pre[j] = min_point;
        }
      }
    }
  }
}