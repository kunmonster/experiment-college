#include "./rand.h"
#include<iostream>
using namespace std;

class Dart{
    private:
    int n;          //投点个数
    double left;    //左边界限
    double right;    //右边界限
    static Rand randNum;
    public:
    double Dart_are(){
        int k=0;
        double x=0.0;
        double y=0.0;
        for(int i=0;i<n;i++){
        x = (this->right-this->left) * this->randNum.generateRand_1()+this->left;

        }
    }
    double Dart_avg(double(*f)(x)){
        double sum = 0;
    for(int i=0;i<n;i++){
        //生成left-right之间的数
        double var_val = (right-left) * randNum.generateRand_1()+left;
        sum+=(*f)(var_val);
    }
    return (right-left) * sum / n;
    }
};


double f(double x);

int main(){
    return 0;
}