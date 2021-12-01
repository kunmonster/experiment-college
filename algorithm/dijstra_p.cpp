#include <iostream>

#define maxSize 1000

using namespace std;

typedef struct ArcNode {
  int adjvex;
  struct ArcNode *nextarc;
} ArcNode;

typedef struct {
  int data;
  ArcNode *firstarc;
} Vnode;

//可以利用结构体整体结构，也可以拆分结构体变为单独搜索
typedef struct {
  Vnode adjlist[maxSize];
  int n, e;
} AGraph;

AGraph *graph;

//插入链表末尾
void insertNode(ArcNode *node, ArcNode *newNode) {
  ArcNode *p = node;
  while (p->nextarc != NULL) {
    p = p->nextarc;
  }
  p->nextarc = newNode;
}

void create() {
  graph = (AGraph *)malloc(sizeof(AGraph));
  cout << "输入顶点的数目: " << endl;
  cin >> graph->n;
  cout << "输入图中边的数目: " << endl;
  cin >> graph->e;

  int u = -1, v = -1;
  for (int i = 0; i < graph->n; i++) {
    graph->adjlist[i].firstarc = NULL;
  }
  ArcNode *node;
  for (int i = 0; i < graph->e; i++) {
    cout << "请输入联通点A与B" << endl;
    cin >> u >> v;
    node = (ArcNode *)malloc(sizeof(ArcNode));
    node->adjvex = v;
    node->nextarc = NULL;
    graph->adjlist[u].data = u;
    if (graph->adjlist[u].firstarc == NULL) {
      //边
      graph->adjlist[u].firstarc = node;
    } else {
      //插入边
      insertNode(graph->adjlist[u].firstarc, node);
    }
  }
}

void travseTree() {
  for (int i = 0; i < graph->n; i++) {
    if (graph->adjlist[i].firstarc != NULL) {
      cout << "与" << i << "连接的点有：";
      ArcNode *p = graph->adjlist[i].firstarc;
      while (p != NULL) {
        cout << p->adjvex << " ";
        p = p->nextarc;
      }
      cout << endl;
    }
  }
}

int main() { return 0; }