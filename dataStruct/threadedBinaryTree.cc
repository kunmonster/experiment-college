#include <bits/stdc++.h>
using namespace std;

typedef struct TreeNode {
  char m_data;
  bool m_ltag;  // ltag表示左指针指向左孩子还是前驱 (ture:前驱;false:左孩子)
  bool m_rtag;  // rtag表示左指针指向右孩子还是后继(true:后继;false:右孩子)
  struct TreeNode* m_lchild;
  struct TreeNode* m_rchild;
  TreeNode(char data = 0, bool ltag = false, bool rtag = false,
           struct TreeNode* lchild = nullptr, struct TreeNode* rchild = nullptr)
      : m_data(data),
        m_ltag(ltag),
        m_rtag(rtag),
        m_lchild(lchild),
        m_rchild(rchild) {}
  TreeNode* operator=(const TreeNode* root) {}
} * ThreadTree;

void PreOrder(const TreeNode* origin, TreeNode* newroot) {
  if (origin) {
  }
}

struct TreeNode* copyTree(const TreeNode* root) {
  TreeNode* res;
  while (root) {
  }
}

char c;
void CreateTree(ThreadTree& root) {
  cin >> c;
  if (c != '#') {
    root = new TreeNode(c);
    CreateTree(root->m_lchild);
    CreateTree(root->m_rchild);
  }
}

void MidThreadTree(ThreadTree& root, ThreadTree& pre) {
  if (root != nullptr) {
    //中序需要先找到最左结点，初始时候pre应为一个空结点
    MidThreadTree(root->m_lchild, pre);
    //找到子树最左结点,该结点没有左结点了，需要把左指针指向前驱
    if (!root->m_lchild) {
      // the lchild exis
      root->m_ltag = true;
      root->m_lchild = pre;
    }
    //前驱存在且没有右子树，将其后继指向当前结点
    if (pre && (pre->m_rchild == nullptr)) {
      pre->m_rchild = root;
      pre->m_rtag = true;
    }
    //将前驱变为当前结点
    pre = root;
    //构造右子树
    MidThreadTree(root->m_rchild, pre);
  }
}

//先序构建线索二叉树
void PreThreadTree(ThreadTree& root, ThreadTree& pre) {
  if (root != nullptr) {
    if (!root->m_lchild) {
      root->m_lchild = pre;
      root->m_ltag = true;
    }
    if (pre && pre->m_rchild == nullptr) {
      pre->m_rchild = root;
      pre->m_rtag = true;
    }
    pre = root;
    PreThreadTree(root->m_lchild, pre);
    PreThreadTree(root->m_lchild, pre);
  }
}
//后序构建线索二叉树
void PostedThreadTree(ThreadTree& root, ThreadTree& pre) {
  if (root != nullptr) {
    //结点存在
    //找到后序的第一个的结点
    PostedThreadTree(root->m_lchild, pre);
    PostedThreadTree(root->m_rchild, pre);
    if (root->m_lchild != nullptr) {
      root->m_lchild = pre;
      root->m_ltag = 1;
    }
    if (pre && pre->m_rchild != nullptr) {
      pre->m_rchild = root;
      pre->m_rtag = 1;
    }
    pre = root;
  }
}

int main() {
  ThreadTree root;
  CreateTree(root);

  return 0;
}