/*
* fkj
* 2021.11.19
* library
*/

#include<iostream>

using namespace std;

/*
*迭代方式计算矩阵连乘法
*paramter: 矩阵数组，最少乘法次数存放，断开点,数组长度
*/
void matrix_mutiplie_iteraion(int * , int ** ,int **,int );


int main(){
    int  arr[] ={1,3,4,2,6};
    int ** min = new int * [5];
    int ** s = new int * [5];
    for(int i=0;i<5;i++){
        min[i] = new int[5];
        s[i] = new int[5];
    }
    matrix_mutiplie_iteraion(arr,min,s,5);
    return 0;
}
void matrix_mutiplie_iteraion(int * matrix_arr,int ** min,int ** s,int len){
    if(!matrix_arr)
    return;
    int i,r,j,k,temp;
    for(i =0;i<len;i++){
        //对角线置0
        min[i][i]=0;
    }
    for(r=2;r<len;r++){
        //从长度为啥开始求两个矩阵间最少乘法次数
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
