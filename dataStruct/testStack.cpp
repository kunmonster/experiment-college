#include "./stack.h"

using namespace std;

int main() {
  Stack<char>* s = new Stack<char>(5);
  s->push('a');
  s->push('b');
  s->push('c');
  s->push('d');
  s->push('e');
  bool isfull = s->full();
  char c = s->top();
  bool empt1 = s->empty();
  s->pop();
  s->pop();
  s->pop();
  s->pop();
  s->pop();
  bool issuccess = s->pop();
  bool empt2 = s->empty();
  return 0;
}