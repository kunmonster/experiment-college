/*
* fkj
* 2021.11.19
* library
*/

#include<iostream>
#include<time.h>
using namespace std;


void generate_matrix(const int , int *);
void matrix_mutiplie_iteraion(int * , int ** ,int **,int );
void track_brackets(int , int , int **);

int main(){
    cout<<"请输入矩阵个数:";
    int num=0;
    cin>>num;

    int i;
    int * arr;
    int ** min = new int *[num+1];
    int ** s = new int * [num+1];
    for(i=0;i<num+1;i++){
        min[i] = new int[num+1];
        s[i] = new int[num+1];
    }
    generate_matrix(num+1,arr);
    matrix_mutiplie_iteraion(arr,min,s,num+1);
    track_brackets(1,num,s);
    system("pause");
    return 0;
}

/**
*生成随机矩阵序列
*paramters : 矩阵数组长度 , 矩阵数组
*/
void generate_matrix(const int num,int * matrix){
    if(!num){
        cout<<"矩阵数量不正确"<<endl;
        exit(1);
    }
    matrix = new int[num];
    srand(time(0));
    for(int i=0;i<num;i++){
        matrix[i] = rand() % 10 + 1;
    }
}
/*
*迭代方式计算矩阵连乘法
*paramter: 矩阵数组，最少乘法次数存放，断开点,数组长度
*/
void matrix_mutiplie_iteraion(int * matrix_arr,int ** min,int ** s,int len){
    if(!matrix_arr)
    return;
    int i,r,j,k,temp;
    for(i =0;i<len;i++){
        //对角线置0
        min[i][i]=0;
    }
    for(r=2;r<len;r++){
        //从长度为2开始求两个矩阵间最少乘法次数
        for(i=1;i<len-r+1;i++){
            j=i+r-1;    //i--j
            min[i][j] = min[i+1][j]+matrix_arr[i-1] * matrix_arr[i] * matrix_arr[j];
            s[i][j] = i;
            for(k = i+1;k < j;k++){
                temp  = min[i][k] + min[k+1][j] + matrix_arr[i-1] * matrix_arr[k] * matrix_arr[j];
                if(min[i][j] > temp){
                    min[i][j] = temp;
                    s[i][j] = k;
                }
            }
            cout<<"["<<i<<":"<<j<<"]"<<"  "<<min[i][j]<<endl;
        }
    }
}

/*
*paramters : 起点矩阵 ， 终点矩阵 ， 断开点存放数组
**/
void track_brackets(int left,int right,int ** s){
      if(left == right) return;
      track_brackets(left,s[left][right],s);
      track_brackets(s[left][right]+1,right,s);
      cout<<"multipl A"<<left<<","<<s[left][right];
      cout<<" and A"<<(s[left][right]+1)<<","<<right<<endl;
}
