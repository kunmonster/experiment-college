#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;  //无穷大
const int MAXN = 1000010;    //最大的点数目

/**
 * 节点
 */
struct Node {
  int v;                                          //序号
  int c;                                          //边的权值
  Node(int _v = 0, int _c = 0) : v(_v), c(_c) {}  //构造
  bool operator<(const Node node) const { return c > node.c; }
};

/**
 *邻接表
 */
struct Edge {
  int v;                                                         //邻接点
  int weight;                                                    //权值
  Edge(int _v = 0, int _weight = 0) : v(_v), weight(_weight) {}  //构造
};

int *pre;              //最短路径
vector<Edge> E[MAXN];  //邻接表

bool s[MAXN];                 //标记该点是否访问过
int dist[MAXN];               //最短距离
priority_queue<Node> disque;  //优先队列(小顶堆)

/**
 * param : 源点
 */
void Dijkstra(int start) {          // start为起点
  memset(s, false, sizeof(s));      //初始化s数组
  memset(dist, INF, sizeof(dist));  //初始化dist数组
  while (!disque.empty()) {
    disque.pop();
  }
  dist[start] = 0;
  disque.push(Node(start, 0));
  ::pre[start] = start;
  Node tmp;
  while (
      !disque
           .empty()) {  //每次取出队首的元素（由于是优先队列，第一个的权值是最小的）
    tmp = disque.top();
    disque.pop();
    int u = tmp.v;
    if (s[u]) continue;
    s[u] = true;
    for (int i = 0; i < E[u].size(); i++) {
      int v = E[u][i].v;
      int weight = E[u][i].weight;
      if (!s[v] && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        disque.push(
            Node(v, dist[v]));  //并且把该点加入队列（便于找与该点相邻的边）
        ::pre[v] = u;  //标记路径
      }
    }
  }
}

/**
 * 添加边
 * 源点 , 终点 , 权值
 */
void addEdge(int u, int v, int w) { E[u].push_back(Edge(v, w)); }

/**
 * 路径打印
 */
void print_path(int len, int start, int end, const int *pre) {
  int temp = end;
  stack<int> path;
  path.push(end);
  while (pre[temp] != (start)) {
    temp = pre[temp];
    path.push(temp);
  }
  path.push(start);
  while (!path.empty()) {
    cout << path.top();
    path.pop();
    if (!path.empty()) cout << "-->";
  }
}
void print_cloeset(const int len, const int start, const int *dis,
                   const int *pre) {
  cout << "第" << start << "个节点到其他节点的最短距离分别为:" << endl;
  cout << "节点"
       << "\t"
       << "距离"
       << "\t"
       << "路径" << endl;

  for (int i = 1; i <= len; i++) {
    cout << i << "\t" << dis[i] << "\t";
    print_path(len, start, i, pre);
    cout << endl;
  }
}
int main() {
  int u, v, w;  //源点,终点,权值
  int st;       //起点
  int n, m;     //点数和边数
  cout << "请输入点数和边数:";
  cin >> n >> m;
  pre = new int[n + 1]{0};
  cout << "请输入联通点A与B和路径权值格式为:[起点] [终点] [权值]" << endl;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    addEdge(u, v, w);
  }
  cout << "输入起点:";
  cin >> st;
  Dijkstra(st);

  print_cloeset(n, st, ::dist, ::pre);
  return 0;
}