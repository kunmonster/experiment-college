#include <bits/stdc++.h>

#include "linklist.h"
using namespace std;



/**
 * 设计一个递归算法，删除不带头节点的单链表L中所有值为X的节点
*/
void delete_all_x(LinkList& nohead, int x) {
    if(!nohead) return;
    if(nohead->data == x){
        auto ndp = nohead;
        nohead = nohead->next;
        delete ndp;
        return delete_all_x(nohead,x);
    }
    return delete_all_x(nohead->next,x);
}



/**
 * 逆序输出带头节点链表
 * 用栈或者直接使用递归
*/

void reverse_print(LinkList & head){

}



int main() {
    auto nohead = create_LinklistWithoutHead(10);
    print_List(nohead);
    // delete_all_x(nohead,1);
    print_List(nohead);


}