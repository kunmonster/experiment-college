#include<bits/stdc++.h>
#include<singlelist.h>
using namespace std;

void DeleteSome(LinkNode* &head,int mink,int maxk){
    if(!head)return;
    LinkNode * pri = head;
    LinkNode * last = head->next;
    while(last){
        if(last->data < maxk && last->data > mink){
            pri->next = last->next;
            delete last;
            last = pri->next;
        }
        else{
            last = last->next;
            pri = pri->next;
        }
    }
}

int main(){
    return 0;
}