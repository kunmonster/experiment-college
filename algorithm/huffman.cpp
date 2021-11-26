/**
 *fkj
 *huffman base heap
 *2021/11/25
 */
#include <string.h>

#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// open file and load in memory

class node {
 private:
  char data;
  unsigned int num;
  node *left;
  node *right;

 public:
  node(const char data, const unsigned int num) {
    this->data = data;
    this->num = num;
  }
  node(const char data, const unsigned int num, node *left, node *right) {
    this->data = data;
    this->num = num;
    this->left = left;
    this->right = right;
  }
  unsigned int getWeight() { return this->num; }
  char getData() { return this->data; }
};

// struct freq {
//   char data;
//   unsigned int num;
//   struct freq *left;
//   struct freq *right;
//   freq(char data, unsigned int num) : data(data), num(num){};
//   freq (char data,unsigned int num,struct freq * left,struct freq * right) :
//   data(data), num(num),left(left),right(right){};
// };

struct cmp {
  bool operator()(node *key1, node *key2) {
    return key1->getWeight() > key2->getWeight();
  }
};

typedef priority_queue<node *, vector<node *>, cmp> pri_queue;
void get_init_queue(const int, const char *, pri_queue *);
void encode(pri_queue *);

int main() {
  char str[] = {'A', 'B', 'A', 'C', 'R', 'B', 'A'};
  pri_queue queue;
  get_init_queue(7, str, &queue);
  encode(&queue);
  return 0;
}
/**
 * 根据出现频率构建最小堆优先队列
 */
void get_init_queue(const int len, const char *str, pri_queue *queue) {
  if (str == NULL) return;
  int i, j;

  int a[256]={0};

  for(i=0;i<len;i++){
    a[str[i]]++;
  }

  for(i=0;i<256;i++){
    if(a[i] != 0){
      node * temp_node = new node((char)i,a[i],NULL,NULL);
      queue->push(temp_node);
    }
  }
}

void encode(pri_queue *queue) {
  while (queue->size() >= 2) {
    //还没完全合并成树
    node *top = queue->top();
    queue->pop();
    node *second = queue->top();
    queue->pop();
    node *f = new node(0, top->getWeight() + second->getWeight(), top, second);
    queue->push(f);
  }
  return;
}