#include <bits/stdc++.h>
using namespace std;

/*
 *the single node of tree
 */
template <typename T>
class Node {
 public:
  T m_data;
  Node* m_left;
  Node* m_right;
  Node(T data = 0, Node* left = nullptr, Node* right = nullptr)
      : m_data(data), m_left(left), m_right(right) {}
  explicit Node(const Node* par) {
    this->m_data = par->m_data;
    this->m_left = par->m_left;
    this->m_right = par->m_right;
  }
  ~Node() {
    delete m_left;
    delete m_right;
  }
};

//先序遍历(recur递归)
template <typename T>
void PreOrder(Node<T>* root) {
  if (!root) return;
  cout << root->m_data << "\t";
  if (root->m_left) PreOrder(root->m_left);
  if (root->m_right) PreOrder(root->m_right);
}

//中序遍历
template <typename T>
void MidOrder(Node<T>* root) {
  if (!root) return;
  if (root->m_left) MidOrder(root->m_left);
  cout << root->m_data << "\t";
  if (root->m_right) MidOrder(root->m_right);
}

//后续遍历
template <typename T>
void PostOrder(Node<T>* root) {
  if (!root) return;
  if (root->m_left) PostOrder(root->m_left);
  if (root->m_right) PostOrder(root->m_right);
  cout << root->m_data << "\t";
}

//层序遍历
template <typename T>
void LevelOrder(Node<T>* root) {
  if (!root) return;
  queue<Node<T>*> tmp_q;
  tmp_q.push(root);
  auto temp = root;
  while ((!tmp_q.empty()) && (temp = tmp_q.front())) {
    tmp_q.pop();
    cout << temp->m_data << "\t";
    if (root->m_left) tmp_q.push(root->m_left);
    if (root->m_right) tmp_q.push(root->m_right);
  }
}
template <typename T, typename Node>
class Tree {
 public:
  Node* m_root;

  Tree(Node* root = nullptr) : m_root(root) {}
  ~Tree() { delete m_root; }
  void createTree() {
    if (this->m_root) {
      cout << "当前树不为空,是否继续建树(将会清除原树)?" << endl;
      cout << "选择:\t是: [1]\t否[2]" << endl;
      int choice = 1;
      cin >> choice;
      switch (choice) {
        case 1:
          this->generateTree();
          break;
        case 2:
          //不建树
          return;
        default:
          this->generateTree();
          break;
      }
    }
    this->generateTree();
  }

  void generateTree() {
    if (this->m_root) {
      queue<Node*> tmp;
      tmp.push(this->m_root);
      auto cur = this->m_root;
      while ((!tmp.empty()) && (cur = tmp.front())) {
        tmp.pop();
        if (cur->m_left) tmp.push(cur->m_left);
        if (cur->m_right) tmp.push(cur->m_right);
        delete cur;
      }
    }
    this->m_root = new Node();
    preCreate(this->m_root);
  }
  T data;
  void preCreate(Node* root) {
    cin >> data;
    if (data == '#'){
      root = nullptr;
      return;
    }
    else {
      root->m_data = data;
      root->m_left = new Node();
      preCreate(root->m_left);
      root->m_right = new Node();
      preCreate(root->m_right);
    }
  }
};

int main() {
  Tree<char, Node<char>>* test = new Tree<char, Node<char>>();
  test->createTree();
  PreOrder(test->m_root);
  cout<<endl;
  MidOrder(test->m_root);
  cout<<endl;
  PostOrder(test->m_root);
  cout<<endl;
  LevelOrder(test->m_root);
  return 0;
}
