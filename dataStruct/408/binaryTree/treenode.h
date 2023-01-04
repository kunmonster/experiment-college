#ifndef _TREE_H_
#define _TREE_H

using namespace std;

typedef struct node {
  int data;
  struct node* left;
  struct node* right;
  node(int m_data):data(m_data),left(nullptr),right(nullptr){}
}* Tree;

Tree pre_createTree(){
  
}

#endif