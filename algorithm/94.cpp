/**
 * fkj
 * 2022.1.16
 * 非递归中序遍历二叉树
 *
 */

#include <bits/stdc++.h>
using namespace std;

class node {
 public:
  int val;
  node* left;
  node* right;
  node(int val, node* left = NULL, node* right = NULL)
      : val(val), left(left), right(right) {}
};

vector<int> travel(node* root) {
  vector<int> res;
  stack<node*> stk;
  node* temp = root;
  while (temp || !stk.empty()) {
    while (temp) {
      stk.push(temp);
      temp = temp->left;
    }
    node* p = stk.top();
    res.push_back(temp->val);
    stk.pop();
    temp = p->right;
  }
  return res;
}

int main() { return 0; }