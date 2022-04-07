#ifndef STACK_H
#define STACK_H
#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class Stack {
 public:
  T* data;
  int m_size = 0;
  int length = 0;
  int m_top = -1;
  Stack(int size = 0) {
    // init
    size = (size && size <= MAX_SIZE) ? size : MAX_SIZE;
    this->m_size = size;
    this->data = new T[size]{T(0)};
  }
  bool full();
  bool empty();
  bool push(T);
  bool pop();
  bool destory();
  T top();
  ~Stack();
};

/**
 * function : 判断栈是否为空
 */
template <typename T>
bool Stack<T>::full() {
  return this->m_top == this->m_size - 1 ? true : false;
}

/**
 * function : 判断栈是否为空
 */
template <typename T>
bool Stack<T>::empty() {
  return length > 0 ? false : true;
}

/**
 * function : 将一个元素压入栈中;
 * paramter : T push_data (需要压入的元素)
 */
template <typename T>
bool Stack<T>::push(T push_data) {
  if (this->full()) return false;
  this->data[++m_top] = push_data;
  this->length++;
  return true;
}

template <typename T>
bool Stack<T>::pop() {
  if (this->empty()) return false;
  this->data[m_top] = T(0);
  --m_top;
  --length;
  return true;
}

template <typename T>
T Stack<T>::top() {
  if (this->empty()) return NULL;
  return this->data[m_top];
}

template <typename T>
bool Stack<T>::destory() {
  this->length = 0;
  this->m_top - 1;
  delete this->data;
  this->data = nullptr;
  return true;
}

template <typename T>
Stack<T>::~Stack() {
  // clear memory of data
  delete this->data;
}

#endif
