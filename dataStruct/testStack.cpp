#include "./stack.h"
#include<stack>

using namespace std;

int main() {
  Stack<char>* s = new Stack<char>(5);
  stack<int> stk;
  stk.top();
  s->push('a');
  s->push('b');
  s->push('c');
  s->push('d');
  s->push('e');
  bool isfull = s->full();
  // char c = s->top();
  // *c = 'm';
  bool empt1 = s->empty();
  s->pop();
  s->pop();
  s->pop();
  s->pop();
  s->pop();
  bool issuccess = s->pop();
  bool empt2 = s->empty();
  bool ssss = s->destory();
  return 0;
}