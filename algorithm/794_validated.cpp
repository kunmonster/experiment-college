#include <iostream>
#include <vector>
using namespace std;
bool win(vector<pair<int, int>> arr, int size) {
  int i = 0;
  int j = 0;
  int row = 0;
  int col = 0;
  int incline = 0;
  int tag = false;
  while (i < size - 1 && row < 3 && col < 3 && incline < 3) {
    bool change = false;
    j = i + 1;
    int temp = i;
    while (j < size) {
      if (arr[temp].first == arr[j].first) {
        row++;
        change = true;
      }
      if (arr[temp].second == arr[j].second) {
        col++;
        change = true;
      }
      if (abs(arr[temp].first - arr[j].first) ==
          abs(arr[temp].second - arr[j].second)) {
        incline++;
        change = true;
      }
      if (change) {
        temp = j;
      }
        j++;

    }
   i++;
  }
  if (row == 3 || col == 3 || incline == 3)
    return true;
  else
    return false;
}

bool validTicTacToe(vector<string>& board) {
  vector<pair<int, int>> x_arr;
  vector<pair<int, int>> o_arr;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 'O')
        o_arr.push_back(pair<int, int>(i, j));
      else if (board[i][j] == 'X') {
        x_arr.push_back(pair<int, int>(i, j));
      } else
        continue;
    }
  }
  int x_size = x_arr.size();
  int o_size = o_arr.size();
  if (x_size != o_size && x_size - 1 != o_size) return false;
  if (x_size == o_size) {
    //当数量一样时,要么选手二赢，要么就不满足
    //判断选手二是否赢，赢了就true，否则false
    if (win(o_arr, o_size)) {
      return true;
    } else {
      return false;
    }
  }
  if (x_size - 1 == o_size) {
    if (win(x_arr, x_size))
      return true;
    else
      return false;
  }
  return false;
}

int main() {
  vector<string> res(3);
  res[0] = "XXX";
  res[1] = "OOX";
  res[2] = "OOX";
  validTicTacToe(res);
  return 0;
}