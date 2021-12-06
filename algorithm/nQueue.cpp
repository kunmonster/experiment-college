/**
*fkj
*2021/12/05
*回溯n后
*/
#include<iostream>
using namespace std;

class Nqueen{
    private:
    bool place(int );      //限界函数
    int n;          //棋盘的行列数
    int * res;      //结果数组，res[i]表示第i行存放的列数
    public:
    Nqueen(int);
    ~Nqueen();
    void BackTrack(int);
};

Nqueen::Nqueen(int n){
    this->n = n;
    this->res = new int[n+1]{0};
}
Nqueen::~Nqueen(){}

bool Nqueen::place(int index){
}
void Nqueen::BackTrack(int index){
if(index > this->n) {
    return;
}
else{
    for(int i=1;i<=this->n;i++){
        res[index] = i;
        if(place(index)){
            BackTrack(index+1);
        } 
    }
}
}
int main(){
    return 0;
}