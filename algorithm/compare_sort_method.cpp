#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int * generateArray(){
    std::cout<<"please input the size of the array:";
    int num = 0;
    std::cin >> num;
    std::cout<<"please input the range of the array element"<<endl;
    int left = 0;
    int right = 0;
    std::cout<<"left:";
    cin>>left;
    std::cout<<endl<<"right:";
    cin>>right;
    srand(time(0));

    int * arr = new int[num];
    for(int i=0;i<num;i++){
        *(arr+i) = rand()%(right-left+1)+left;
    }
    return arr;
}


int main(){
    int * arr =  generateArray();

    return 0;
}