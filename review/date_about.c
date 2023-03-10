#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

enum week {
  MonDay = 1,
  TuesDay,
  WendesDay,
  ThursDay,
  FriDay,
  SatuarDay,
  SunDay
};

struct date {
  int year;
  int month;
  int day;
};

int check_day(int startMon, int startDay, int endMon, int endDay);
int check_week(int, enum week);
int is_year(int);
int sub_day(char[], char[]);
void print_date(int, int);
void stole_vegetables() {
  int hour;
  int min;
  int start_hour = 13;
  int start_min = 15;
  while (scanf("%d:%d", &hour, &min) != EOF) {
    int end_hour = (start_hour + hour) % 24;
    int end_min = 0;
    if ((start_min + min) >= 60) {
      end_hour++;
      end_min = (start_min + min) % 60;
    }
    else end_min = start_min+min;
    printf("%02d:%02d",end_hour,end_min);
  }
}

int main() {
  // int startMon = 0;
  // int startDay = 0;
  // int endMon = 0;
  // int endDay = 0;
  // scanf("%d%d%d%d", &startMon, &startDay, &endMon, &endDay);
  // int day = check_day(startMon, startDay, endMon, endDay);
  // enum week weekday;
  // weekday = ThursDay;

  // printf("%d", check_week(day, weekday));

  // char s[9];
  // char e[9];
  // scanf("%s", &s);
  // scanf("%s", &e);

  // printf("\n");

  // int res = sub_day(s, e);

  // printf("%d", res);

  // int year, day;
  // scanf("%d%d", &year, &day);
  // print_date(year, day);
  stole_vegetables();

  return 0;
}

int check_day(int startMon, int startDay, int endMon, int endDay) {
  if (startMon < 1 || startMon > 12) return -1;
  if (endMon < 1 || endMon > 12) return -1;
  if (startDay > days[startMon - 1] || startDay < 0) return -1;
  if (endDay > days[endMon - 1] || endDay < 0) return -1;
  if (endMon < startMon) return -1;

  if (endMon == startMon) {
    if (endDay <= startDay)
      return -1;
    else
      return endDay - startDay;
  }

  int sum = days[startMon - 1] - startDay;
  for (int i = startMon + 1; i < endMon; i++) {
    sum += days[i];
  }
  sum += endDay;
  return sum;
}
int check_week(int days, enum week weekday) {
  return (weekday + (days % 7)) % 7;
}
int is_year(int year) {
  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return 1;
  return 0;
}

int check_day_s(struct date start, struct date end) {
  if (start.year <= end.year) {
    if (1 <= start.month <= 12 && 1 <= end.month <= 12) {
      // 闰年置位
      if (is_year(start.year) == 1)
        days[1] = 29;
      else
        days[1] = 28;
      if (1 <= start.day <= days[start.month - 1]) {
        if (is_year(end.year) == 1)
          days[1] = 29;
        else
          days[1] = 28;
        if (1 <= end.day <= days[end.month - 1]) {
          // 满足情况
          if (start.year == end.year) {
            // 同一年
            return check_day(start.month, start.day, end.month, end.day) + 1;
          } else {
            // 中间隔年了
            int sum = 0;
            for (int i = start.year + 1; i < end.year; i++) {
              if (is_year(i))
                sum += 366;
              else
                sum += 365;
            }
            if (is_year(start.year) == 1)
              days[1] = 29;
            else
              days[1] = 28;
            for (int i = start.month + 1; i <= 12; i++) sum += days[i - 1];
            sum += (days[start.month - 1] - start.day) + 1;
            if (is_year(start.year) == 1)
              days[1] = 29;
            else
              days[1] = 28;
            for (int i = 1; i < end.month; i++) sum += days[i - 1];
            sum += end.day;
            return sum;
          }
        }
      }
    }
  }
  return -1;
}

int sub_day(char start[], char end[]) {
  if (strlen(start) != 8 || strlen(end) != 8) return -1;
  int startYear = 0, startMon = 0, startDay = 0;
  int endYear = 0, endMon = 0, endDay = 0;
  int i = 0;
  for (i = 0; i <= 3; i++) {
    startYear = startYear * 10 + (start[i] - '0');
    endYear = endYear * 10 + (end[i] - '0');
  }
  for (i = 4; i < 6; i++) {
    startMon = startMon * 10 + (start[i] - '0');
    endMon = endMon * 10 + (end[i] - '0');
  }
  for (i = 6; i < 8; i++) {
    startDay = startDay * 10 + (start[i] - '0');
    endDay = endDay * 10 + (end[i] - '0');
  }
  struct date start_s = {startYear, startMon, startDay};
  struct date end_s = {endYear, endMon, endDay};

  return check_day_s(start_s, end_s);
}

void print_date(int year, int day) {
  if (1 <= year <= 3000 && 1 <= day <= 366) {
    int sum = 0;
    if (is_year(year))
      days[1] = 29;
    else
      days[1] = 28;
    int i = 0;
    for (int i = 0; i < 12; i++) {
      int temp = sum + days[i];
      if (temp > day) {
        printf("%d-%d-%d", year, i + 1, days[i] - (temp - day));
        return;
      } else if (temp == day) {
        printf("%d-%d-%d", year, i + 1, days[i]);
        return;
      } else {
        sum += days[i];
      }
    }
  }
}
