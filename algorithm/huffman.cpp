/**
 *fkj
 *huffman base heap
 *2021/11/25
 */
#include <string.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

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
  node *getLeft() { return left; }
  node *getRight() { return right; }
};

//
struct cmp {
  bool operator()(node *key1, node *key2) {
    return key1->getWeight() > key2->getWeight();
  }
};

struct Bit {
  unsigned value : 1;
  
  Bit(int value) : value(value) {}
};

//
typedef map<char, vector<struct Bit>> code_Map;
typedef priority_queue<node *, vector<node *>, cmp> pri_queue;

//
void init_queue(const int *, pri_queue *);
node *create_huffman_tree(pri_queue *);
void get_huffman_code(vector<Bit>, node *root, code_Map *);
int *getfile(const char *filePath);
void encode(const code_Map, const char *);
void decode(char *, node *);

int main() {
  cout << "输入文件名:" << endl;
  string path;
  cin >> path;
  int *arr = getfile(path.c_str());
  pri_queue queue;
  init_queue(arr, &queue);
  node *root = create_huffman_tree(&queue);
  code_Map code_map;
  vector<Bit> code;
  get_huffman_code(code, root, &code_map);
  encode(code_map, path.c_str());
  return 0;
}

/**
 * 根据出现频率构建最小堆优先队列
 */
void init_queue(const int *arr, pri_queue *queue) {
  for (int i = 0; i < 256; i++) {
    if (arr[i] != 0) {
      node *temp_node = new node((char)i, arr[i], NULL, NULL);
      queue->push(temp_node);
    }
  }
}

/**
 * 根据优先队列创建哈夫曼树
 */
node *create_huffman_tree(pri_queue *queue) {
  while (queue->size() >= 2) {
    //还没完全合并成树
    node *top = queue->top();
    queue->pop();
    node *second = queue->top();
    queue->pop();
    node *f = new node(0, top->getWeight() + second->getWeight(), second, top);
    queue->push(f);
  }
  return queue->top();
}

/**
 *根据哈夫曼树得到每个字符对应的编码,用map存放
 **/
void get_huffman_code(vector<Bit> code, node *root,
                      code_Map *code_map) {
  if (!root) {
    return;
  }
  if (root->getData() != 0) {
    //叶子节点
    code_map->insert(std::pair<char,vector<Bit>>(root->getData(),code));
    return;
  }
  code.push_back(Bit(0));
  get_huffman_code(code, root->getLeft(), code_map);
  code.pop_back();
  code.push_back(Bit(1));
  get_huffman_code(code, root->getRight(), code_map);
}

int *getfile(const char *filePath) {
  ifstream inFile;
  inFile.open(filePath, ios::binary);
  if (!inFile) {
    //文件打开失败
    cout << "文件打开失败,程序退出" << endl;
    exit(1);
  }
  int *weight = new int[256]{0};
  int temp;
  while ((temp = inFile.get()) != EOF) {
    weight[temp]++;
  }
  inFile.close();
  return weight;
}
void encode(const code_Map code_map, const char *path) {
  string res;
  ifstream inFile;
  ofstream outFile;
  inFile.open(path, ios::binary);
  if (!inFile) {
    //文件打开失败
    cout << "文件打开失败,程序退出" << endl;
    exit(1);
  }
  char c;
  while ((c = inFile.get()) != EOF) {
    cout << c;
    vector<Bit> str = code_map.at(c);
    for (int i = 0; i < str.size(); i++) {
      res.push_back(str[i].value);
    }
  }

  inFile.close();

  char new_path[256];
  strcpy(new_path, path);
  strcat(new_path, ".huffman");

  outFile.open(new_path, ios::out);

  outFile.write(res.c_str(), res.size());
  outFile.close();
}