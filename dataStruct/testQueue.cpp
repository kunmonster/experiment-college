#include <bits/stdc++.h>

#include "cycleQueue.h"

using namespace std;

int main(){
  CycleQueue<int> q(5);
  bool f1 = q.isEmpty();
  bool f2 = q.isFull();
  q.push(0);
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);
  q.isEmpty();
  q.isFull();
  int a = q.Front();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  return 0;
}