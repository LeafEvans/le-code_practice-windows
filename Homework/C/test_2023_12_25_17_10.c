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

typedef enum Piece { KING, QUEEN, BISHOP, PAWN, KNIGHT, ROOK, SPACE } Piece;

typedef enum Color { WHITE, BLACK } Color;

typedef struct Square {
  Piece piece;
  Color color;
} Square;

void initBoard(Square (*ptr)[8][8]) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if ((i == 0 || i == 7) && (j == 0 || j == 7))
        (*ptr)[i][j].piece = ROOK;
      else if (i == 1 || i == 6)
        (*ptr)[i][j].piece = PAWN;
      else if ((i == 0 || i == 7) && (j == 1 || j == 6))
        (*ptr)[i][j].piece = KNIGHT;
      else if ((i == 0 || i == 7) && (j == 2 || j == 5))
        (*ptr)[i][j].piece = BISHOP;
      else
        (*ptr)[i][j].piece = SPACE;
      if ((i + j) % 2 == 0)
        (*ptr)[i][j].color = BLACK;
      else
        (*ptr)[i][j].color = WHITE;
    }
  }
  (*ptr)[0][3].piece = QUEEN;
  (*ptr)[7][3].piece = QUEEN;
  (*ptr)[0][4].piece = KING;
  (*ptr)[7][4].piece = KING;
}

int main(void) {
  Square board[8][8];
  initBoard(&board);
  return 0;
}
