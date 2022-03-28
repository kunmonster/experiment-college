#include <bits/stdc++.h>
using namespace std;

enum State { ERROR, SUCCESS };

template <typename T>
class Node {
 public:
  T data;
  Node* next;
  Node(T data = 0, Node* next = NULL) {
    this->data = data;
    this->next = next;
  }
  ~Node();
};

template <typename T, typename Node>
class linkList {
 public:
  //默认构造
  // default constructor
  Node *head, *tail;
  int size = 0;
  linkList() {
    this->head = new Node();
    this->tail = head;
    this->size = 0;
  }

  //初始构造
  linkList(Node* head, Node* tail = NULL) {
    this->head = head;
    Node* temp = head;
    while (temp && temp->next) temp = temp->next;
    this->tail = temp;
  }

  //拷贝构造
  //深拷贝
  linkList(const linkList* initlinkList) {
    Node* temp = initlinkList->head;
    int size = initlinkList->size;
    this->size = size;
    Node* cur = this->head = new Node();

    while (temp) {
      cur = new Node(temp->data, temp->next);
      tail = cur;
      cur = cur->next;
    }
  }

  bool empty() {
    return this->head == this->tail || this->size == 0 ? true : false;
  }

  // opreation
  State insert(T data) {
    //默认插在链表尾部
    //表为空
    this->tail->next = new Node(data);
    if (!this->tail->next)
      return State::ERROR;
    else {
      //插入成功
      this->tail = this->tail->next;
      this->size++;
      return State::SUCCESS;
    }
  }

  State insert(T data, int index) {
    if (index == 0) {
      if (this->insertHead(data)) return State::SUCCESS;
    } else {
      if (this->empty())
        return State::ERROR;
      else {
        auto cur = head;
        int i = 1;
        while (cur && i <= index) {
          cur = cur->next;
          i++;
        }
        Node* newnode = new Node(data, cur->next);
        cur->next = newnode;
        return State::SUCCESS;
      }
    }
  }

  State insertHead(T data) {
    Node* newnode = new Node(data);
    newnode->next = this->head;
    this->head = newnode;
    this->size++;
    return State::SUCCESS;
  }

  State remove(int index) {
    if (index <= 0 || index > this->size || this->empty()) return State::ERROR;
    int i = 1;
    Node* temp = new Node();
    temp->next = this->head;
    while (temp) {
      if (i == index) {
        temp->next = temp->next->next;
        return SUCCESS;
      }
      i++;
    }
    return State::ERROR;
  }

  // wait to finish
  T getElemetByIndex(int index) {
    if (index <= 0 || index > this->size || this->empty()) return NULL;
    auto cur = this->head;
    while (cur && index >= 1) {
      cur = cur->next;
      index--;
    }
    return cur->data;
  }

  State reverseList() {}

  ~linkList();
};

int main() {
  linkList<char, Node<char>>* a = new linkList<char, Node<char>>();
  a->insert('a');
  a->insert('b');
  return 0;
}