#include <iostream>
#include <stack>
using namespace std;

#define MAX_INT 2147483647

void dijstra(int, int, int *, int *, int [][5]);
void print_path(int, int, int, int *);
int main() {
  int arr[5][5] = {{0, 10, MAX_INT, 30, 100},
                   {MAX_INT, 0, 50, MAX_INT, MAX_INT},
                   {MAX_INT, MAX_INT, 0, MAX_INT, 10},
                   {MAX_INT, MAX_INT, 20, 0, 60},
                   {MAX_INT, MAX_INT, MAX_INT, MAX_INT, 0}};
  
  int point_num = 5;
  int dis[5]={0};
  int pre[5]={0};
  dijstra(point_num,1,dis,pre,arr);
  print_path(5,1,5,pre);
  return 0;
}

/**
 *dijstra 单源最短路径
 *节点数量,起点,最短距离数组,最短路径的前一个节点,节点网
 */
void dijstra(int point_num, int start, int *dis, int *pre, int g[][5]) {
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
      if ((!s[j]) && (dis[j] < temp)) {
        min_point = j;
        temp = dis[j];
      }
    }
    s[min_point] = true;

    //更新dis
    for (j = 0; j < point_num; j++) {
      if ((!s[j]) && (g[min_point][j] < MAX_INT)) {
        int update_dis = g[min_point][j] + dis[min_point];
        if (update_dis < dis[j]) {
          dis[j] = update_dis;
          pre[j] = min_point;
        }
      }
    }
  }
}

void print_path(int len, int start, int end, int *pre) {
  int temp = end - 1;
  stack<int> path;
  path.push(end);
  while (pre[temp] != (start - 1)) {
    temp = pre[temp];
    path.push(temp + 1);
  }
  path.push(start);
  while (!path.empty()) {
    cout << path.top();
    path.pop();
    if (!path.empty()) cout << "-->";
  }
}