#ifndef _CYCLE_QUEUE_H_
#define _CYCLE_QUEUE_H_

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CycleQueue {
 public:
  T* contain_arr;
  int size = 0, rear = 0, front = 0;
  int max_size = 0;
  CycleQueue(int queue_size) {
    this->contain_arr = new T[queue_size];
    this->max_size = queue_size;
    if (!this->contain_arr) {
      cout << "创建失败!" << flush;
      abort();
    }
  }

  /**
   *descrption : 返回队列是否为空
   */
  bool isEmpty() { return size == 0 ? true : false; }
  //判断队列是否已满
  bool isFull() { return size == max_size; }
  //入队
  bool push(T data) {
    if (this->isFull()) {
      cout << "队列已满,入队失败" << endl;
      return false;
    }
    this->contain_arr[rear % max_size] = data;
    ++rear;
    rear %= max_size;
    ++size;
    return true;
  }
  //出队
  bool pop() {
    if (this->isEmpty()) {
      cout << "队列为空!出队失败" << endl;
      return false;
    }
    this->contain_arr[front++] = 0;
    --size;
    ++front;
    front %= max_size;
    return true;
  }

  T Front() {
    if (this->isEmpty()) {
      cout << "队列为空!" << endl;
      return NULL;
    }
    return this->contain_arr[front];
  }
};

#endif