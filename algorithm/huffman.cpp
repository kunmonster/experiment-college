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

#define Zero 255

class node {
 private:
  unsigned char data;
  unsigned int num;
  node *left;
  node *right;

 public:
  node(const unsigned char data, const unsigned int num) {
    this->data = data;
    this->num = num;
  }
  node(const unsigned char data, const unsigned int num, node *left,
       node *right) {
    this->data = data;
    this->num = num;
    this->left = left;
    this->right = right;
  }
  int getWeight() { return this->num; }
  unsigned char getData() { return this->data; }
  node *getLeft() { return this->left; }
  node *getRight() { return this->right; }
};

//
struct cmp {
  bool operator()(node *key1, node *key2) {
    return key1->getWeight() > key2->getWeight();
  }
};

//
typedef vector<char> code;
typedef map<unsigned char, vector<char>> code_Map;
typedef priority_queue<node *, vector<node *>, cmp> pri_queue;

//
void init_queue(int *, pri_queue *);
node *create_huffman_tree(pri_queue *);
void get_huffman_code(vector<char>, node *root, code_Map *);
int *getfile(const char *filePath);
void encode(const code_Map, const char *);
void decode(char *, node *);
unsigned char *getfilestream(const char *);
void decode_1(int, unsigned char *, node *, const char *);
void menu();

int all_size = 0;
int old_byte = 0;

int main() {
  menu();
  return 0;
}

/**
 * 根据出现频率构建最小堆优先队列
 */
void init_queue(int *arr, pri_queue *queue) {
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
  unsigned char temp;
  int old_size = 0;
  while (inFile.read((char *)&temp, sizeof(temp))) {
    weight[temp]++;
    old_size++;
  }
  ::old_byte = old_size;
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
}

/**
 * 从压缩文件中读取数据
 */
unsigned char *getfilestream(const char *filepath) {
  fstream inFile(filepath, ios::app | ios::in | ios::binary);
  if (!inFile) return NULL;

  inFile.seekg(0, ios::end);
  int size = inFile.tellg();
  inFile.seekg(0, ios::beg);
  unsigned char *str = new unsigned char[size]{0};
  stack<unsigned char> temp_stack;
  int i = 0;
  int num = 1;
  inFile.read((char *)(str), size);
  inFile.close();
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
  ::all_size = 8 * size;
  return deal;
}

/**
 *解码递归版本,参数原因弃用
 **/
// void decode(vector<unsigned char> str, node *root, string *res) {
//   if (!root || str.empty()) return;

//   if (root->getData() != 0) {
//     if (root->getData() == 257)
//       res->push_back(0);
//     else
//       res->push_back(root->getData());
//     return;
//   }

//   if (str.back() == 0) {
//     str.pop_back();
//     decode(str, root->getLeft(), res);
//   } else {
//     str.pop_back();
//     decode(str, root->getRight(), res);
//   }
// }

/**
 * 解码并写入文件
 */
void decode_1(int len, unsigned char *str, node *root, const char *filepath) {
  if (len == 0) return;
  int i = 0;
  unsigned char buf[1024];
  int index = 0;
  node *temp = root;
  ofstream outFile;
  outFile.open(filepath, ios::out | ios::binary | ios::app);
  if (!outFile) return;
  while (i < len && temp && index < 1024) {
    if (temp->getData() != 0) {
      if (temp->getData() == 255) {
        buf[index] = 0;
      } else {
        buf[index] = temp->getData();
      }
      index++;
      if (index >= 1023) {
        //缓冲区满
        outFile.seekp(0, ios::end);
        outFile.write((char *)&buf, 1024);
        index = 0;
        memset(&buf, 0, 1024);
      }
      temp = root;
    }
    if (temp->getData() == 0) {
      if (str[i] == 0) {
        temp = temp->getLeft();
      } else {
        temp = temp->getRight();
      }
      i++;
    }
  }
  if (index != 0) {
    outFile.seekp(0, ios::end);
    for (int l = 0; l < index; l++) {
      outFile.write((char *)&buf[l], sizeof(buf[l]));
    }
    // outFile.write((char *)&buf, sizeof(buf));
  }
  outFile.close();
}

void menu() {
  cout << "[1]:压缩文件"
       << "\t"
       << "[2]:解压文件" << endl;
  cout << "请选择:";
  int c;
  node *root;
  while (true) {
    cin >> c;
    if (c == 1) {
      //压缩文件
      string path;
      cout << "请输入文件路径:";
      cin >> path;
      int *arr = getfile(path.c_str());
      pri_queue queue;
      init_queue(arr, &queue);
      root = create_huffman_tree(&queue);
      code_Map code_map;
      vector<char> code;
      get_huffman_code(code, root, &code_map);
      encode(code_map, path.c_str());
      string encode_path = path + ".huffman";
      getfilestream(encode_path.c_str());
      double rate = all_size/8 / (double)::old_byte;
      cout << "压缩完毕,文件名为:" << encode_path << endl;
      cout<<"压缩率为:"<<rate<<endl;
    }
    if (c == 2) {
      //解压文件
      string path;
      cout << "请输入文件路径:";
      cin >> path;
      unsigned char *ss = getfilestream(path.c_str());
      // int size = sizeof(*ss);
      string new_path;
      cout << "请输入解压后文件路径:";
      cin >> new_path;
      decode_1(::all_size, ss, root, new_path.c_str());
      cout << "解压完毕!" << endl;
    }
  }
}