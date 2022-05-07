#include <bits/stdc++.h>
using namespace std;

/*
 *the single node of tree
 */
template <typename T>
class Node {
 public:
  T m_data;
  node* m_next;
  Node(T data = 0, Node* next = nullptr) : m_data(data), m_next(next) {}
  explicit Node(const Node* par) {
    this->m_data = par->m_data;
    this->m_next = par->m_next;
  }
  ~node() { delete m_next; }
};

template <typename T>
class Tree {
 public:
  Node* m_root;

  Tree(Node* root = nullptr) : m_root(root) {}
  ~Tree() { delete m_root; }

  //先序遍历
  void NLR() {
    if (!this->m_root) {
      cout << "树为空" << endl;
      return;
    }
    auto cur = m_root;
    while (cur) {
    }
  }
};

int main() { return 0; }
