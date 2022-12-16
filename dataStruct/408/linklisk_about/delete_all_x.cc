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
      //找到更小的节点
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

int main() {
  auto nohead = create_LinklistWithHead(5);
  print_List(nohead);
  // delete_all_x(nohead,1);
  //   reverse_print(nohead);
  //   delete_SoleMin(nohead);
  //   reverse_List(nohead);
//   sort_List(nohead);
  print_List(nohead);
}