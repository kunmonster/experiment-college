/**
 *fkj
 * 二叉树的线索化(前序，中序，后序)，以及线索遍历
 * 2022/5/7
 * */
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
  TreeNode* operator=(const TreeNode* root) {
    TreeNode* res = new TreeNode(root->m_data, root->m_ltag, root->m_rtag,
                                 root->m_lchild, root->m_rchild);
    return res;
  }
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

//中序构建线索二叉树
//最后一个结点是右下结点，需要处理
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
//最后一个结点是最右下结点,需要处理后继为空
void PreThreadTree(ThreadTree& root, ThreadTree& pre) {
  if (root != nullptr) {
    bool tag = false;
    if (root->m_lchild == nullptr) {
      //看原来结点的左子树是否存在,注意若不存在,那么就不需要线索化左子树了，否则将会线索其前驱
      tag = true;
      root->m_lchild = pre;
      root->m_ltag = true;
    }
    if (pre && pre->m_rchild == nullptr) {
      pre->m_rchild = root;
      pre->m_rtag = true;
    }
    pre = root;
    //需要判断原来的左子树是否存在，不存在就不能线索化左子树，否则将会线索其前驱结点
    if (!tag) PreThreadTree(root->m_lchild, pre);
    PreThreadTree(root->m_rchild, pre);
  }
}
//后序构建线索二叉树
//最后一个节点是root结点，不需要做额外处理
void PostedThreadTree(ThreadTree& root, ThreadTree& pre) {
  if (root != nullptr) {
    //结点存在
    //找到后序的第一个的结点
    PostedThreadTree(root->m_lchild, pre);
    PostedThreadTree(root->m_rchild, pre);
    if (root->m_lchild == nullptr) {
      root->m_lchild = pre;
      root->m_ltag = 1;
    }
    if (pre && pre->m_rchild == nullptr) {
      pre->m_rchild = root;
      pre->m_rtag = 1;
    }
    pre = root;
  }
}

void Mid(ThreadTree& root, ThreadTree& pre) {
  MidThreadTree(root, pre);
  pre->m_rchild = nullptr;
  pre->m_rtag = true;
  pre = nullptr;
}
void Pre(ThreadTree& root, ThreadTree& pre) {
  PreThreadTree(root, pre);
  pre->m_rchild = nullptr;
  pre->m_rtag = true;
  pre = nullptr;
}

int main() {
  //测试用例
  // ABD##E##C#G##
  ThreadTree root;
  CreateTree(root);
  ThreadTree pre = new TreeNode();
  // MidThreadTree(root, pre);
  return 0;
}