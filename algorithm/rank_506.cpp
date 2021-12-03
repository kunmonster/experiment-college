/**
 *优先队列解力扣506
 *
 */
#include <iostream>
#include <queue>
using namespace std;

struct P {
  int index;
  int score;
  P(int index = 0, int score = 0) : index(index), score(score) {}
  bool operator<(const struct P other) const { return score < other.score; }
};

int main() {
  int num[5] = {10, 3, 8, 9, 4};
  priority_queue<P> pri_que;
  for (int i = 0; i < 5; i++) {
    // int temp = num[i];

    pri_que.push(P(i, num[i]));
  }
  vector<string> rank(5);
  int i = 0;
  while (!pri_que.empty() && i < 5) {
    if (i == 0) {
      rank[pri_que.top().index] = "Gold Medal";
    } else if (i == 1) {
      rank[pri_que.top().index] = "Silver Mdeal";
    } else if (i == 2) {
      rank[pri_que.top().index] = "Bronze Medal";
    } else {
      rank[pri_que.top().index] = i + 1;
    }
    i++;
    pri_que.pop();
  }
  return 0;
}