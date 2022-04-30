#include <bits/stdc++.h>
using namespace std;

map<int, bool> bigMonth{{1, 1}, {3, 1},  {5, 1}, {7, 1},
                        {8, 1}, {10, 1}, {12, 1}};
map<int, bool> smallMonth{{4, 1}, {6, 1}, {9, 1}, {11, 1}};

bool isLeapYear(int year) {
  if (year % 100 == 0 && year % 400 == 0) {
    return true;
  } else if (year % 100 != 0 && year % 4 == 0) {
    return true;
  } else {
    return false;
  }
}

void NextDay(int year, int month, int day) {
  // if (!isdigit(year)) {
  //   cout << "年份输入异常" << endl;
  //   return;
  // } else if (!isdigit(month)) {
  //   cout << "月份输入异常" << endl;
  //   return;
  // } else if (!isdigit(day)) {
  //   cout << "日输入异常" << endl;
  //   return;
  // } else {

  if ((year < 1900) || (year > 2050)) {
    cout << "年份输入非法" << endl;
    return;
  } else if ((month < 1) || (month > 12)) {
    cout << "月份输入非法" << endl;
    return;
  } else if ((day < 1) || (day  > 31)) {
    cout << "日输入非法" << endl;
    return;
  } else {
    if (month != 2 && month != 12) {
      if (bigMonth[month]) {
        //大月
        if (day == 31) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      } else {
        //小月
        if (day == 30) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      }
    } else if (month == 12) {
      //为12月
      if (day == 31) {
        ++year;
        month = 1;
        day = 1;
      } else {
        ++day;
      }
    } else {
      // 2月
      if (isLeapYear(year)) {
        //闰年
        if (day == 29) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      } else {
        if (day == 28) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      }
    }
    cout << year << " : " << month << " : " << day << endl;
  }
}

int main() {
  int year, month, day;
  while (true) {
    cin >> year >> month >> day;
    NextDay(year, month, day);
  }

  return 0;
}