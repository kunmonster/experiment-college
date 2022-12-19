#include <bits/stdc++.h>

#include "linklist.h"
using namespace std;

/**
 * 1.设计一个递归算法，删除不带头节点的单链表L中所有值为X的节点
 */
void delete_all_x(LinkList& nohead, int x) {
  if (!nohead) return;
  if (nohead->data == x) {
    auto ndp = nohead;
    nohead = nohead->next;
    delete ndp;
    return delete_all_x(nohead, x);
  }
  return delete_all_x(nohead->next, x);
}

/**
 * 2.逆序输出带头节点链表
 * 用栈或者直接使用递归
 */

void reverse_print(const LinkList& head) {
  if (!head) return;
  reverse_print(head->next);
  std::cout << head->data << "\t";
}

/**
 * 3.删除带头结点链表中最小的节点，最小节点唯一
 */
void delete_SoleMin(LinkList& head) {
  if (!head || !head->next) return;
  auto pri = head;
  auto slow = head;
  auto cur = head->next;
  int base = INT32_MAX;
  while (cur) {
    if (cur->data < base) {
      base = cur->data;
      pri = slow;
    }
    slow = cur;
    cur = cur->next;
  }
  auto temp = pri->next;
  pri->next = temp->next;
  delete temp;
  temp = nullptr;
}

/**
 * 4.就地逆置带头节点链表,使用常数个辅助空间
 */

void reverse_List(LinkList& head) {
  node* res = new node(-1);
  while (head) {
    auto next = head->next;
    head->next = res->next;
    res->next = head;
    head = next;
    next = nullptr;
  }
  head = res->next;
}

/**
 *  5.使一个带头节点的单链表，递增有序排列
 */
void sort_List(LinkList& head) {
  auto pri = head->next;
  if (!pri) return;
  auto cur = pri->next;
  while (cur) {
    if (cur->data < pri->data) {
      // 找到更小的节点
      auto slow = head;
      auto fast = slow->next;
      while (fast && fast->data <= cur->data) {
        slow = fast;
        fast = fast->next;
      }
      auto temp = cur->next;
      cur->next = fast;
      slow->next = cur;
      pri->next = temp;
      cur = temp;
    } else {
      pri = cur;
      cur = cur->next;
    }
  }
}

/**
 * 6.将链表分为两个链表,偶数和基数拆开
 */
void split_List(LinkList& head, LinkList& odd, LinkList& even) {
  if (!head->next) return;
  int i = 1;
  auto odd_c = odd;
  auto even_c = even;
  auto cur = head->next;
  while (cur) {
    auto temp = cur->next;
    if ((i % 2) == 0) {
      cur->next = nullptr;
      even_c->next = cur;
      even_c = even_c->next;
    } else {
      cur->next = nullptr;
      odd_c->next = cur;
      odd_c = odd_c->next;
    }
    i++;
    cur = temp;
  }
}

/**
 * 7.将链表分为奇偶两个链表，且元素逆置
 * 方案一:先拆分，再逆置两个链表
 * 方案二:直接使用头插一次性完成
 */
void split_List_reverse(LinkList& head, LinkList& odd, LinkList& even) {
  if (!head->next) return;
  int i = 1;
  auto cur = head->next;
  while (cur) {
    auto temp = cur->next;
    if ((i % 2) == 0) {
      // 偶数情况,加入even链表,使用头插
      cur->next = even->next;
      even->next = cur;
    } else {
      cur->next = odd->next;
      odd->next = cur;
    }
    ++i;
    cur = temp;
  }
}

/**
 * 8.链表去重
 */
void delete_Repeat(LinkList& head) {
  if (!head->next) return;
  unordered_map<int, int> num_map;
  auto cur = head->next;
  while (cur) {
    if (num_map.count(cur->data) == 0)
      num_map.insert(pair<int, int>(cur->data, 1));
    else {
      num_map[cur->data]++;
    }
    cur = cur->next;
  }
  auto slow = head;
  cur = head->next;
  while (cur) {
    if (num_map[cur->data] > 1) {
      num_map[cur->data]--;
      slow->next = cur->next;
      delete cur;
      cur = slow->next;
    } else {
      slow = cur;
      cur = cur->next;
    }
  }
}

/**
 * 9.将两个升序链表合并为一个逆序的降序链表，使用原来的节点(不能创建新节点)(无头节点)
 * 解法一:先合并升序链表,再反转
 */
node * merge_TList_Reverse(LinkList& l1, LinkList& l2) {
  node  * res = new node();
  while (l1 && l2) {
    if (l1->data > l2->data) {
      auto temp = l2->next;
      l2->next = res->next;
      res->next = l2;
      l2 = temp;
      temp = nullptr;
    } else if (l1->data < l2->data) {
      // l1节点小于l2节点
      auto temp = l1->next;
      l1->next = res->next;
      res->next = l1;
      l1 = temp;
      temp = nullptr;
    } else {
      // 相等
      auto temp1 = l1->next;
      auto temp2 = l2->next;
      l1->next = res->next;
      l2->next = l1;
      res->next = l2;
      l2 = temp2;
      l1 = temp1;
      temp1 = nullptr;
      temp2 = nullptr;
    }
  }
  while (l1) {
    // l1还未用完,头插到链表
    auto temp = l1->next;
    l1->next = res->next;
    res->next = l1;
    l1 = temp;
    temp = nullptr;
  }
  while (l2) {
    auto temp = l2->next;
    l2->next = res->next;
    res->next = l2;
    l2 = temp;
    temp = nullptr;
  }
  return res;
}

int main() {
  auto nohead1 = create_LinklistWithoutHead(10);
  print_List(nohead1);

  auto nohead2 = create_LinklistWithoutHead(10);
  print_List(nohead2);

  // auto odd = new node(-1);
  // auto even = new node(-1);

  // delete_all_x(nohead,1);
  //   reverse_print(nohead);
  //   delete_SoleMin(nohead);
  //   reverse_List(nohead);
  //   sort_List(nohead);
  // split_List_reverse(nohead, odd, even);
  // delete_Repeat(nohead);
  auto result = merge_TList_Reverse(nohead1, nohead2);
  print_List(result);
  // print_List(nohead);
  // print_List(odd->next);
  // print_List(even->next);
}