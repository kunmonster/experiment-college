#include <bits/stdc++.h>
using namespace std;

class Kmp {
 public:
  string parent_string;
  string pattern_string;
  int* next;
  int* nextval;
  Kmp(string S, string T) : parent_string(S), pattern_string(T) {
    next = new int[T.length()]{-1};
    nextval = new int[T.length()]{-1};
  }
  void get_Next() {
    //这里j从0开始索引
    int j = 0, k = -1;
    while (j < pattern_string.length()) {
      //当第j+1个字符失配,这时候找到k,k就是next[j],然后比较第j个字符和第k个是否相等，如果相等的话说明第j+1个元素失配的时候只需要找到从k+1位置重新匹配即可
      if (k == -1 || pattern_string[j] == pattern_string[k]) {
        ++k;          // k往后滑
        ++j;          // j往后滑
        next[j] = k;  // next[j+1] = k+1;

      } else {
        //当不等的时候,这时候继续找P1-k的比较位置
        k = next[k];
      }
    }
  }
  void get_NextVal() {
    //这里j从0开始索引
    int j = 0, k = -1;
    while (j < pattern_string.length()) {
      //当第j+1个字符失配,这时候找到k,k就是next[j],然后比较第j个字符和第k个是否相等，如果相等的话说明第j+1个元素失配的时候只需要找到从k+1位置重新匹配即可
      if (k == -1 || pattern_string[j] == pattern_string[k]) {
        ++k;  // k往后滑
        ++j;  // j往后滑
        // next[j] = k;  // next[j+1] = k+1;
        if (pattern_string[k] != pattern_string[j]) {
          //滑了过后比较不相等,说明k位置的元素与产生失配的元素p[j]不相等,这时候将下个比较位置滑到k
          nextval[j] = k;
        } else {
          //比较要滑的位置和产生失配位置的元素,这两个元素相等,说明不能滑到这里,应该继续往下滑,即滑到next[next[j]],再比较,直到找到与j元素不相等的元素
          nextval[j] = nextval[k];
        }

      } else {
        //当不等的时候,这时候继续在P1-k当中找比较位置,其实就是将k位置失配时候的位置赋给k,再往下递归查找
        k = next[k];
      }
    }
    for (int i = 0; i < pattern_string.length(); i++) {
      cout << nextval[i] << endl;
    }
  }
};

int main() {
  Kmp* a = new Kmp("TEST", "ababaaababaa");
  a->get_Next();
  cout << "nextval" << endl;
  a->get_NextVal();
  return 0;
}