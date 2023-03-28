#include <stdio.h>
#include <stdlib.h>

// 边结点
typedef struct Edge
{
    int start;
    int end;
    int weight;
    edge next;
} *edge;

// 表节点
struct vertex
{
    int index;
    edge *next;
};

typedef struct graph
{
    struct vertex *v_Arr;
    int size;
} *G;

void init(G, int);

int main()
{
    return 0;
}

void init(G g, int size)
{
    g = (G)malloc(sizeof(struct graph));
    if(g==NULL)exit(1);
    int n;
    int tag = 0;
    printf("请输入点的个数:\n");
    while(scanf("%d",&n) != EOF && n<=0){
        printf("个数输入有误,请重新输入,你当前输入为%d",n);
    }
    
    printf("请选择有向图或者无向图:\n[1]:无向图\t[2]:有向图\t(默认为无向图)");
    
    while(scanf("%d",&tag)!=EOF && tag != 1 && tag != 2){
        printf("输入有误,请重新输入\n");
    }
    //初始化表节点
    g->v_Arr = (struct vertex * )malloc(sizeof(struct vertex) * n);
    g->size = n;
    //输入边
    int start,end,weight;
    printf("请输入起始点和结束点以及权值用空格隔开\n");
    while(scanf("%d%d%d",&start,&end,&weight)!=EOF){

    }
    
}