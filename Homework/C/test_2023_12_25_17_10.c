typedef struct date {
  int month;
  int day;
  int year;
} date;

typedef struct time {
  int hours;
  int minutes;
  int seconds;
} time;

int day_of_year(date d) {
  int days_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int day_of_year = d.day;

  if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
    days_of_month[2]++;

  for (int i = 1; i < d.month; ++i) day_of_year += days_of_month[i];

  return day_of_year;
}

int compare(struct date d1, struct date d2) {
  int day1 = day_of_year(d1);
  int day2 = day_of_year(d2);

  if (day1 == day2) return 0;

  return day1 > day2 ? 1 : -1;
}

time split_time(long total_seconds) {
  time t = {0};
  t.hours = total_seconds / 3600;
  total_seconds %= 3600;
  t.minutes = total_seconds / 60;
  t.seconds = total_seconds % 60;
  return t;
}

int main(void) { return 0; }
