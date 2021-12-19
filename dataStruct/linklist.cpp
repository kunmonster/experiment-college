#include<iostream>
using namespace std;

template <typename T>

typedef struct _NODE_{
    T data;
    struct _NODE_ * next;
    _NODE_(T data , struct _NODE_ * next=NULL) : data(data) , next(next){}
}node;

node * createLinkList();
bool insertLinkNode(int,node,node *);
bool removeLinkNode(int,node *);
T getDataByIndex(int);
int getSize(node *);

int main(){
    return 0;
}

node * createLinkList(){
    node * head = new node();
    T data;
    while(std::cin>>data){
        node * temp = new node(data,NULL);
        head->next = temp;
    }
}