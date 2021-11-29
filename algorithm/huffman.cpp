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
#include <stack>
#include <vector>

using namespace std;

#define Zero 257

class node {
 private:
  int data;
  unsigned int num;
  node *left;
  node *right;

 public:
  node(const int data, const unsigned int num) {
    this->data = data;
    this->num = num;
  }
  node(const int data, const unsigned int num, node *left, node *right) {
    this->data = data;
    this->num = num;
    this->left = left;
    this->right = right;
  }
  int getWeight() { return this->num; }
  unsigned int getData() { return this->data; }
  node *getLeft() { return left; }
  node *getRight() { return right; }
};

//
struct cmp {
  bool operator()(node *key1, node *key2) {
    return key1->getWeight() > key2->getWeight();
  }
};

//
typedef vector<char> code;
typedef map<unsigned int, vector<char>> code_Map;
typedef priority_queue<node *, vector<node *>, cmp> pri_queue;

//
void init_queue(const int *, pri_queue *);
node *create_huffman_tree(pri_queue *);
void get_huffman_code(vector<char>, node *root, code_Map *);
int *getfile(const char *filePath);
void encode(const code_Map, const char *);
void decode(char *, node *);
void getfilestream(char *,node *);
void decode_1(int,unsigned char * , node *,vector<char> *);


int main() {
  cout << "输入文件名:" << endl;
  string path;
  cin >> path;
  int *arr = getfile(path.c_str());
  pri_queue queue;
  init_queue(arr, &queue);
  node *root = create_huffman_tree(&queue);
  code_Map code_map;
  vector<char> code;
  get_huffman_code(code, root, &code_map);
  encode(code_map, path.c_str());
  char new_path[256];
  strcpy(new_path, path.c_str());
  strcat(new_path, ".huffman");
  getfilestream(new_path,root);
  // decode(new_path, root);
  return 0;
}

/**
 * 根据出现频率构建最小堆优先队列
 */
void init_queue(const int *arr, pri_queue *queue) {
  for (int i = 0; i < 256; i++) {
    if (arr[i] != 0) {
      node *temp_node;
      if (i == 0) {
        temp_node = new node(Zero, arr[0], NULL, NULL);
      } else {
        temp_node = new node(i, arr[i], NULL, NULL);
      }
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
void get_huffman_code(vector<char> code, node *root, code_Map *code_map) {
  if (!root) {
    return;
  }
  if (root->getData() != 0) {
    //叶子节点
    code_map->insert(std::pair<int, vector<char>>(root->getData(), code));
    return;
  }
  code.push_back(0);
  get_huffman_code(code, root->getLeft(), code_map);
  code.pop_back();
  code.push_back(1);
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
  ifstream inFile;
  ofstream outFile;
  inFile.open(path, ios::binary);
  if (!inFile) {
    //文件打开失败
    cout << "文件打开失败,程序退出" << endl;
    exit(1);
  }
  char c;
  vector<unsigned char> res;
  char temp;
  int j = 1;
  while ((c = inFile.get()) != EOF) {
    vector<char> str;
    if (c == 0) {
      str = code_map.at(Zero);
    } else if (c < 0) {
      int index = (int)c + 256;
      str = code_map.at(index);
    } else {
      str = code_map.at((int)c);
    }
    for (int i = 0; i < str.size(); i++) {
      if ((j) % 8) {
        if (str[i] == 1) {
          temp |= 0x1;
          temp <<= 1;
        } else {
          temp <<= 1;
        }
        j++;
      } else {
        //超过8位了
        if (str[i] == 1) {
          temp |= 0x1;
        }
        unsigned char sign_code = temp;
        res.push_back(sign_code);
        temp &= 0x0;
        j = 1;
      }
    }
  }

  inFile.close();

  char new_path[256];
  strcpy(new_path, path);
  strcat(new_path, ".huffman");
  outFile.open(new_path, ios::binary);
  for (int i = 0; i < res.size(); i++) {
    outFile.write((char *)&res[i], sizeof(res[i]));
  }
  // outFile << EOF;
}

void getfilestream(char *filepath, node *root) {
  fstream inFile(filepath, ios::app | ios::in | ios::binary);
  if (!inFile) return;

  inFile.seekg(0, ios::end);
  int size = inFile.tellg();
  inFile.seekg(0, ios::beg);
  unsigned char *str = new unsigned char[size]{0};
  // vector<unsigned char> deal(8 * size);
  stack<unsigned char> temp_stack;
  int i = 0;
  int num = 1;
  inFile.read((char *)(str), size);
  unsigned char *deal = new unsigned char[8 * size]{0};
  for (int j = 0; j < size; j++) {
    int m = 0;
    for (m; m < 8; m++) {
      temp_stack.push((str[j] >> m) & 1);
    }
    m = 0;
    while (!temp_stack.empty() && m < 8) {
      deal[j * 8 + m] = temp_stack.top();
      temp_stack.pop();
      m++;
    }
  }
  // for (int n = 0; n < 8 * size; n++) cout << (int)deal[n];
  vector<char> *ss;
  decode_1(8 * size,deal,root,ss);
}

void decode(vector<unsigned char> str, node *root, string *res) {
  if (!root || str.empty()) return;

  if (root->getData() != 0) {
    if (root->getData() == 257)
      res->push_back(0);
    else
      res->push_back(root->getData());
    return;
  }

  if (str.back() == 0) {
    str.pop_back();
    decode(str, root->getLeft(), res);
  } else {
    str.pop_back();
    decode(str, root->getRight(), res);
  }
}
void decode_1(int len, unsigned char *str, node *root,vector<char> * res) {
  if (len == 0) return;
  int i = 0;
  node *temp = root;
  while (i < len && temp) {
    if (temp->getData() != 0) {
      if (temp->getData() == 257) {
        res->push_back(0);
      } else
        res->push_back((char)root->getData());
    }
    if (root->getData() == 0) {
      if (str[i] == 0) {
        temp = temp->getLeft();
      } else {
        temp = temp->getRight();
      }
    }
    if (!temp) temp = root;
    i++;
  }
}