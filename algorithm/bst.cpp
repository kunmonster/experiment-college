/**
 *fkj
 *108.将有序数组转换为搜索二叉树
 */
#include <iostream>
#include <vector>
using namespace std;

typedef struct _BSTNODE_ {
  int data;
  struct _BSTNODE_* left;
  struct _BSTNODE_* right;
  _BSTNODE_(int p_data, struct _BSTNODE_* p_left = NULL,
            struct _BSTNODE_* p_right = NULL)
      : data(p_data), left(p_left), right(p_right) {}
} bstnode;

vector<int> sorted_arr;  //有序数组

bstnode* sortedArrayToBST(const vector<int>& arr, int left, int right) {
  if (left > right) {
    return NULL;
  }
  int mid = left + (right - left) / 2;
  bstnode* root = new bstnode(arr[mid]);
  root->left = sortedArrayToBST(arr, left, mid - 1);
  root->right = sortedArrayToBST(arr, mid + 1, right);
  return root;
}
int main() {
  vector<int> arr{-10, -3, 0, 5, 9};
  bstnode* res = sortedArrayToBST(arr, 0, 4);
  return 0;
}