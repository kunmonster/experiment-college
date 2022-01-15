
/**
 *fkj
 *leet 3
 *2022.1.14
 */
#include <iostream>
#include <string>

using namespace std;

int getLenOfOrdSub(string s) {
  int len = s.size();
  //字符串为空
  if (!len) return 0;
  //字符串只有一个字符
  else if (len == 1) {
    return 1;
  } else {
    const char* cstr = s.c_str();
    int number[256];
    for (int i = 0; i < 256; i++) {
      number[i] = -1;
    }
    int max_len = -1;
    int ahead = 0, behind = 0;
    while (ahead < len) {
      //未出现过
      if (number[(int)cstr[ahead]] == -1)
        number[cstr[ahead]] = ahead;
      else if (number[(int)cstr[ahead]] != ahead) {
        //已经出现过,此时将后面的指针滑到之前的位置,然后将位置置为当前的位置

        // if(number[(int)cstr[number[(int)cstr[ahead]]+1]] !=
        // number[(int)cstr[ahead-1]])
        if (behind <= number[(int)cstr[ahead]])
          behind = number[(int)cstr[ahead]] + 1;
        number[(int)cstr[ahead]] = ahead;
      }
      max_len = max_len < ahead - behind + 1 ? ahead - behind + 1 : max_len;
      ahead++;
    }
    return max_len;
  }
}

int main() {
  string s = "dvdf";
  string s1 = "abcdef";
  int res = getLenOfOrdSub(s);
  int res1 = getLenOfOrdSub(s1); 
  cout << res<<endl<<res1;
  return 0;
}