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
  ~Node() {}
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
    cur = cur->next;

    while (temp) {
      cur = new Node(temp->data, temp->next);
      tail = cur;
      cur = cur->next;
    }
  }

  //判断链表是否为空
  bool empty() {
    return this->head == this->tail || this->size == 0 ? true : false;
  }

  //清空链表
  bool clear() {
    if (this->empty()) return true;
    Node* cur = this->head;
    auto temp = new Node();
    while (cur) {
      temp = cur->next;
      delete cur;
      cur = temp;
    }
    delete temp;
    temp = nullptr;
    delete cur;
    cur = nullptr;
    this->tail = this->head = nullptr;
    this->size = 0;
    return true;
  }

  // opreation
  // pass
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

  // param : T , int
  // description : the data to insert , the sequence of the data
  State insert_after(T data, int index) {
    if (index < 0 || index > this->size) {
      return State::ERROR;
    } else if (index == 0) {
      if (this->insertHead(data)) return State::SUCCESS;
      return State::ERROR;
    } else {
      if (this->empty())
        return State::ERROR;
      else {
        if (index == this->size) {
          //直接在尾节点后面插入
          this->tail->next = new Node(data);
          this->tail = this->tail->next;
          this->size++;
          return State::SUCCESS;
        }
        auto cur = head;
        int i = 0;
        while (cur && i < index) {
          cur = cur->next;
          i++;
        }
        Node* newnode = new Node(data, cur->next);
        cur->next = newnode;
        newnode = NULL;
        this->size++;
        return State::SUCCESS;
      }
    }
  }

  // param : T
  // description : insert the data before the first node
  State insertHead(T data) {
    if (this->empty()) {
      if (this->head != nullptr)
        this->head->next = new Node(data);
      else
        this->head = new Node(0, new Node(data));
      this->tail = this->head->next;
      return State::SUCCESS;
    }
    Node* newnode = new Node(data, this->head->next);
    this->head->next = newnode;
    this->size++;
    newnode = NULL;
    return State::SUCCESS;
  }

  // param : int
  // remove the certain element in index
  State remove(int index) {
    if (index <= 0 || index > this->size || this->empty())
      return State::ERROR;
    else if (index == 1) {
      auto temp = head->next;
      head->next = head->next->next;
      delete temp;
      temp = nullptr;
      this->size--;
      return State::SUCCESS;
    } else {
      int i = 0;
      Node* cur = head;
      while (cur && i < index - 1) {
        cur = cur->next;
        i++;
      }
      auto needdel = cur->next;
      cur->next = cur->next->next;
      delete needdel;
      needdel = nullptr;
      while (cur && cur->next) cur = cur->next;
      this->tail = cur;
      cur = nullptr;
      this->size--;
      return State::ERROR;
    }
  }

  State pop() { return this->remove(this->size); }

  State push(T data) { return this->insert(data); }

  // param : int
  // description : get the certain element in index
  T getElemetByIndex(int index) {
    if (index <= 0 || index > this->size || this->empty()) return 0;
    auto cur = this->head;
    while (cur && index >= 1) {
      cur = cur->next;
      index--;
    }
    T res = cur->data;
    cur = nullptr;
    return res;
  }

  // description : reverse the linklist
  State reverseList() {
    if (this->empty())
      return State::ERROR;
    else {
      auto cur = new Node();
      cur = head->next;
      this->tail = cur;
      while (cur && cur->next) {
        auto tmp = cur->next;
        cur->next = tmp->next;
        tmp->next = head->next;
        head->next = tmp;
        tmp = nullptr;
      }
      cur = nullptr;
      return State::SUCCESS;
    }
  }

  ~linkList();
};

int main() {
  linkList<char, Node<char>>* a = new linkList<char, Node<char>>();
  // a->insert('a');
  // a->insert('b');
  // a->insert_after('c', 2);
  // a->insert_after('d', 3);
  // a->insert_after('e', 1);
  // a->insert_after('f', 3);
  // a->insert_after('g', 4);
  // a->reverseList();
  // a->insert('z');
  // a->remove(1);
  // char s = a->getElemetByIndex(7);
  // a->remove(7);
  // a->pop();
  // a->push('x');
  // // char s1 = a->getElemetByIndex(2);
  // // char s2 = a->getElemetByIndex(3);
  // a->clear();
  // // bool res2 = a->empty();
  return 0;
}