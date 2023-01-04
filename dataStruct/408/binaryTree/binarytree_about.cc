#include <bits/stdc++.h>

#include "treenode.h"
using namespace std;

/**
 * 非递归,统计高度
 */
int count_height(Tree root) {
  int max = 1;
  int height = 1;
  stack<node *> stk;
  while (root || !stk.empty()) {
    if (root) {
      stk.push(root);
      height++;
      max = height > max ? height : max;
      root = root->left;
    } else {
      root = stk.top();
      stk.pop();
      root = root->right;
    }
  }
  return height;
}

void main() {}