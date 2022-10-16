#include <bits/stdc++.h>
#include"singlelist.h"
using namespace std;



/**
 * 2012年程序题
 * 获取倒数第K个节点
 * 注意最后Fast指针指向NULL，K为正整数,不可能为0,即尾节点为序号为1
 * 此题有头节点
*/
int getTheCountDownK(const LinkNode* list, int k) {
  const LinkNode* slow = list;
  const LinkNode* fast = list;
  while (k-- && fast != nullptr) {
    fast = fast->next;
  }
  while (fast != nullptr) {
    slow = slow->next;
    fast = fast->next;
  }
  if (slow) {
    cout << slow->data;
    return 1;
  }
  return 0;
}











int main() { return 0; }