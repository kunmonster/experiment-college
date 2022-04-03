#include "linklist.h"

#include <bits/stdc++.h>

using namespace std;

int main() {
  linkList<char, Node<char>>* a = new linkList<char, Node<char>>();
  a->insert('a');
  a->insert('b');
  a->insert_after('c', 2);
  a->insert_after('d', 3);
  a->insert_after('e', 1);
  a->insert_after('f', 3);
  a->insert_after('g', 4);
  a->reverseList();
  a->insert('z');
  a->remove(1);
  char s = a->getElemetByIndex(7);
  a->remove(7);
  a->pop();
  a->push('x');
  // char s1 = a->getElemetByIndex(2);
  // char s2 = a->getElemetByIndex(3);
  a->clear();
  // bool res2 = a->empty();
  return 0;
}