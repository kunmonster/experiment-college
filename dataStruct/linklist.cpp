#include <iostream>
using namespace std;

template <typename T>

class Node {
 private:
  T data;
  Node* next;

 public:
  // Node<T>(void):data(NULL),next(NULL){}
  Node<T>(T data = T(), Node<T>* next = NULL) : data(data), next(next) {}
  void setNext(Node<T>* next) { this->next = next; }
  void setData(T data) { this->data = data; }
  Node<T>* getNext() { return this->next; }
};

template <typename T>
class LinkList {
 private:
  Node<T>* head;
  int len;

 public:
  //初始化构造
  LinkList() : head(new Node<T>()), len(0) {}
  //拷贝构造
  LinkList(Node<T>* node);
  //创建链表
  void createLinkList();
  //插入元素,index为索引
  bool insertNode(int index, Node<T>& node);
  //删除链表第index个元素
  bool removeNode(int index);
  //根据索引修改元素
  bool alterDataByIndex(int index, T data);
  //通过索引获取元素
  T getDataByIndex(int index);
  void getLen();
  void clear();
};
template <typename T>
void LinkList<T>::createLinkList() {
  T data;
  Node<T>* temp = head;
  while (cin >> data) {
    Node<T>* tmp = new Node<T>(data, NULL);
    temp->setNext(tmp);
    temp = temp->getNext();
  }
}
template <typename T>
bool LinkList<T>::insertNode(int index, Node<T>& node) {
  int i = 0;
  Node<T>* temp = head;
  while (i <= index && temp) {
    temp = temp->getNext();
    i++;
  }
  if (!temp) return false;
  Node<T>* after = temp->getNext();
  temp->setNext(node);
  node->setNext(after);
  return true;
}

template <typename T>
bool LinkList<T>::removeNode(int index) {
  Node<T>* temp = head;
  int i = 0;
  while (i < index - 1) {
    temp = temp->getNext();
    i++;
  }
  if (!temp) return false;
  Node<T>* temp_next = temp->getNext();
  temp->setNext(temp_next->getNext());
  delete temp_next;
  temp_next = NULL;
  return true;
}
template <typename T>

bool LinkList<T>::alterDataByIndex(int index, T data) {
  Node<T>* temp = head;
  int i = 0;
  while (i < index) {
    temp = temp->getNext();
    i++;
  }
  if (!temp) return false;
  temp->setData(data);
  return true;
}
template <typename T>
void LinkList<T>::getLen() {
  int i = 0;
  Node<T>* temp = head;
  while (temp->getNext()) {
    i++;
    temp = temp->getNext();
  }
}
int main() {
  LinkList<char>* link = new LinkList<char>();
  link->createLinkList();
  return 0;
}
