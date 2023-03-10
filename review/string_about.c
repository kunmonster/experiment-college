#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 统计第二个参数中第一个参数中每个字符出现的次数
void count_charNum(char *, char *);
// 在保持原有顺序的条件下将数字字符移动到字母后面
void move_numAfterChar();
// 交换数组两个元素
void swap(char *, char *);
// 统计大写字母的个数
void count_UpperCHAR();

// 将首字母大写
void upper_first();

// 统计单词字母个数
void count_word_charNum();
int main() {
  //   move_numAfterChar();
  // count_UpperCHAR();
  // upper_first();
  count_word_charNum();
  return 0;
}

void count_charNum(char *p, char *t) {}

void move_numAfterChar() {
  char s[105];
  scanf("%s", s);
  int len = strlen(s);
  int slow = 0, fast = 0, cur = 0;
  while (cur < len) {
    if ('0' <= s[cur] && s[cur] <= '9') {
      // 找到连续数字串
      slow = cur;
      int i = 0;
      for (i = (cur + 1); i < len; i++) {
        if (!('0' <= s[i] && s[i] <= '9')) {
          fast = i - 1;
          break;
        }
      }
      int sub_len = (fast - slow) + 1;
      // 找到后面的连续字符串,与其比较长度
      i = fast + 1;
      int count = 0;
      while (i < len && !('0' <= s[i] && s[i] <= '9')) {
        count++;
        i++;
      }

      // 后面连续字符串的长度大于等于前面的字符串,直接交换过后,然后从fast处开始遍历
      // count为0表示后面没有字母了已经
      if (count == 0) break;
      if (count >= sub_len) {
        for (int j = slow; j <= fast; j++) {
          swap(&s[j], &s[j + sub_len]);
        }
        cur = fast;
        continue;
      } else {
        int temp = count;
        // 后面的连续字符串小于前面的数字序列,先交换后面的,然后再交换前面的和后面的
        for (int j = fast; j >= slow && temp > 0; temp--, j--) {
          swap(&s[j], &s[j + count]);
        }
        // 交换完成
        // 将cur置韦slow位置
        cur = slow;
        continue;
      }
      cur++;
    } else
      cur++;
  }
  printf("\n移动后:%s", s);
}

void swap(char *a, char *b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

void count_UpperCHAR() {
  char s[105];
  scanf("%s", s);
  int count_time[26];
  memset(&count_time, 0, sizeof(int) * 26);
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    count_time[s[i] - 'A']++;
  }
  for (int i = 0; i < 26; i++) {
    printf("%c:%d\n", (i + 'A'), count_time[i]);
  }
}

void upper_first() {
  char s[101];
  while (gets(s) != NULL) {
    int tag = 1;
    int len = strlen(s);
    printf("转换前:%s\n", s);
    for (int i = 0; i < len; i++) {
      if (s[i] <= 'z' && s[i] >= 'a' && tag == 1) {
        // 转换为大写
        s[i] = s[i] - 32;
        tag = 0;
      } else if (s[i] == ' ' && tag == 0)
        tag = 1;

      else
        continue;
    }
    printf("转换后:%s\n", s);
  }
}
void count_word_charNum() {
  char s[101];
  while (gets(s) != NULL) {
    int len = strlen(s);
    if (s[len - 1] != '.') {
      printf("字符串输入不正确,必须以.结尾");
      return;
    }
    int count = 0;
    int tag = 0;
    for (int i = 0; i < len - 1; i++) {
      if (s[i] != ' ') {
        count++;
        tag = 0;
      } else if (tag == 0) {
        tag = 1;
        printf("%d ", count);
        count = 0;
      } else {
        tag = 1;
      }
    }
    printf("%d\n", count);
  }
}