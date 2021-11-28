#include<iostream>
using namespace std;

#define MAX_INT 2147483648

void dijstra(int,int ,int *,int *, int **,int **);

int main(){
    return 0;
}


/**
*dijstra 单源最短路径
*point_num
*/
void dijstra(int point_num,int start ,int * dis, int * pre,int ** m,int ** g){
    if(!point_num) return;
    //维护一个标记数组，记录第n个点是否在特殊路径集合中
    bool s[point_num]={false};
    int i;
    s[start-1] = true;
    for(i=0;i<point_num;i++){
        dis[i] = g[start-1][i];
        s[i] = true;
    }

}