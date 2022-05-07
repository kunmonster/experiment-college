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
  //   cout << "��������쳣" << endl;
  //   return;
  // } else if (!isdigit(month)) {
  //   cout << "�·������쳣" << endl;
  //   return;
  // } else if (!isdigit(day)) {
  //   cout << "�������쳣" << endl;
  //   return;
  // } else {

  if ((year < 1900) || (year > 2050)) {
    cout << "�������Ƿ�" << endl;
    return;
  } else if ((month < 1) || (month > 12)) {
    cout << "�·�����Ƿ�" << endl;
    return;
  } else if ((day < 1) || (day > 31)) {
    cout << "������Ƿ�" << endl;
    return;
  } else {
    if (month != 2 && month != 12) {
      if (bigMonth[month]) {
        //����
        if (day == 31) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      } else {
        //С��
        if (day == 30) {
          ++month;
          day = 1;
        } else {
          ++day;
        }
      }
    } else if (month == 12) {
      //Ϊ12��
      if (day == 31) {
        ++year;
        month = 1;
        day = 1;
      } else {
        ++day;
      }
    } else {
      // 2��
      if (isLeapYear(year)) {
        //����
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