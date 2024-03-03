#include <stdio.h>

/* int main(int argc, char** argv) {
  float salary;
  printf("\aEnter your desired monthly salary:");
  printf("$_______\b\b\b\b\b\b\b");
  scanf("%f", &salary);
  printf("\n\t$%.2f a month is $%.2f a year.", salary, salary * 12.0);
  printf("\rGee!\n");
  return 0;
} */
/* int main(void) {
  float num = FLT_MIN;
  num /= 2.0f;
  printf("%f", num);
  return 0;
} */
/* int main(void) {
  printf("\aStartled by thr sudden sound, Sally shouted,\n");
  printf("\"By the Great Pumpkin, what was that!\"\n");
  return 0;
} */
/* int main(void) {
  float num = 0.0f;
  printf("Enter a float-point value: ");
  scanf("%f", &num);
  printf("fixed-point notation: %.6f\n", num);
  printf("exponential notation: %e\n", num);
  printf("p notation: %.2a\n", num);
  return 0;
} */
/* int main(void) {
  unsigned long long age = 0;
  unsigned long long seconds = 0;
  scanf("%llu", &age);
  seconds = age * 31560000;
  printf("%llu\n", seconds);
  return 0;
} */
/* int main(void) {
  float a = 0.0f;
  scanf("%f", &a);
  float b = a * 950 / 3.0e-23;
  printf("%lf", b);
  return 0;
} */
/* int main(void) {
  float foot = 0.0f;
  scanf("%f", &foot);
  printf("%f\n", foot * 2.54);
  return 0;
} */
/* int main(void) {
  float cup_count = 0.0f;
  float pint = 0.0f;
  float ounce = 0.0f;
  float number_of_spoons = 0.0f;
  float number_of_teaspoons = 0.0f;
  scanf("%f", &cup_count);
  pint = cup_count / 2.0;
  ounce = cup_count * 8;
  number_of_spoons = cup_count * 2;
  number_of_teaspoons = number_of_spoons * 2;
  printf("%f %f %f %f %f\n", cup_count, pint, ounce, number_of_spoons,
         number_of_teaspoons);
  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen(
      "C:\\Code\\CodePractice\\Homework\\C\\2024\\test_2024_2_25\\data\\test."
      "txt",
      "w");
  char data[] = "Hello World!";
  if (pf == NULL) {
    printf("%s\n", strerror(errno));
    return 1;
  }

  fwrite(data, sizeof(char), sizeof(data), pf);
  fclose(pf);
  pf = NULL;

  return 0;
} */
/* #include <inttypes.h>
#include <stdio.h>

int main(void) {
  int32_t me32;

  me32 = 45933945;
  printf("First, assume int32_t is int: ");
  printf("me32 = %d\n", me32);
  printf("Next, let's not make any assumption.\n");
  printf("Instead, use a \"macro\" from inttypes.h: ");
  printf("me32 = %" PRId32 "\n", me32);
  return 0;
} */
/* int main(void) {
  float a = -1.23;
  printf("%+#8.0f", a);
  return 0;
} */
/* #define PAGES 959
int main(void) {
  printf("*%d*\n", PAGES);
  printf("*%2d*\n", PAGES);
  printf("*%10d*\n", PAGES);
  printf("*%-10d*\n", PAGES);
  return 0;
} */
/* int main(void) {
  const double RENT = 3852.99;

  printf("*%f*\n", RENT);
  printf("*%e*\n", RENT);
  printf("*%4.2f*\n", RENT);
  printf("*%3.1f*\n", RENT);
  printf("*%10.3f*\n", RENT);
  printf("*%10.3E*\n", RENT);
  printf("*%+4.2f*\n", RENT);
  printf("*%010.2f*\n", RENT);

  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>

int main(void) {
  char str[20] = "FAFJvskw";
  printf("*%-10s*\n", str);

  // 使用相对路径打开文件
  FILE *file = fopen(
      "C:\\Code\\CodePractice\\Homework\\2024\\test_2024_2_25\\data\\test.txt",
      "w");

  if (file != NULL) {
    fputs(str, file);
    fclose(file);
    file = NULL;
  } else {
    printf("Failed to open file\n");
  }

  return 0;
}
 */
/* int main(void) {

  char str[10] = {0};

  for (int i = 0; i < 10; ++i) {
    scanf(" %c", &str[i]);
  }

  printf("%s", str);

  return 0;
} */
/* int main(void) {
  unsigned width, precision;
  int number = 256;
  double weight = 242.5;

  printf("Enter a field width:\n");
  scanf("%d", &width);
  printf("The number is :%*d\n", width, number);
  printf("Now enter a width and a precision:\n");
  scanf("%d %d", &width, &precision);
  printf("Weight = %*.*f\n", width, precision, weight);

  return 0;
} */
/* int main(void) {
  int n;

  printf("Please enter three integers:\n");
  scanf("%*d %*d %d", &n);
  printf("The last integer was %d\n", n);

  return 0;
} */
/* #include <inttypes.h>
#include <stdio.h>

int main(void) {
  int_least8_t a = 32;
  printf("%" PRIdLEAST8 "\n", a3wsz3szwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww);
  return 0;
} */
/* #include <stdio.h>
#define BOOK "War and Peace"

int main(void) {
  float cost = 12.88;
  float percent = 80.0;
  printf("This copy of \"%s\" sells for $%.2f.\n", BOOK, cost);
  printf("That is %.f%% of list.\n", percent);
  return 0;
} */
/* int main(void) {
  char first_name[20];
  char last_name[20];

  printf("Enter your first name and last name:\n");
  scanf("%s %s", first_name, last_name);
  printf("%s, %s", last_name, first_name);

  return 0;
}
 */
/*
int main(void) {
  char name[20];
  printf("输入你的名字:");
  scanf("%s", name);
  printf("\"%s\"\n", name);
  printf("\"%20s\"\n", name);
  printf("\"%-20s\"\n", name);
  printf("%*s\n", (int)sizeof(name) + 3, name);
  return 0;
} */
/* int main(void) {
  float a = 0.0f;
  scanf("%f", &a);
  printf("The input is %.1f or %.1e.\n", a, a);
  printf("The input is % .3f or %.3E.\n", a, a);
  return 0;
} */
/* int main(void) {
  float height = 0.0f;
  char name[20];

  scanf("%s %f", name, &height);
  printf("%s, you are %.3f feet tall", name, height);

  return 0;
} */
/* int main(void) {
  char first_name[20];
  char last_name[20];

  scanf("%s %s", first_name, last_name);
  printf("%s %s\n", first_name, last_name);
  printf("%*lld %*lld\n", (int)strlen(first_name), strlen(first_name),
         (int)strlen(last_name), strlen(last_name));
  printf("%-*lld %-*lld\n", (int)strlen(first_name), strlen(first_name),
         (int)strlen(last_name), strlen(last_name));
  return 0;
} */
/* #include <stdio.h>

int main(void) {
  float megabits = 0.0f;
  float megabytes = 0.0f;
  scanf("%f %f", &megabits, &megabytes);
  printf("%.2f", megabytes * 8 / megabits);
  return 0;
} */
/* #include <float.h>
#include <stdio.h>

int main(void) {
  double a = 1.0 / 3.0;
  float b = 1.0 / 3.0;

  printf("%.6f %.6lf\n", a, b);
  printf("%.12f %.12lf\n", a, b);
  printf("%.16f %.16lf\n", a, b);
  printf("%d %d\n", FLT_DIG, DBL_DIG);

  return 0;
} */
/* #include <stdio.h>

#define MILES_TO_KILOMETERS 1.609
#define GALLONS_TO_LITERS 3.785

int main(void) {
  double miles, gallons;

  printf("请输入行驶的英里数和消耗的汽油量（以空格分隔）：");
  scanf("%lf %lf", &miles, &gallons);

  double miles_per_gallon = miles / gallons;
  double kilometers_per_liter =
      (miles * MILES_TO_KILOMETERS) / (gallons * GALLONS_TO_LITERS);

  printf("每加仑汽油行驶的英里数：%.2lf\n", miles_per_gallon);
  printf("每升汽油行驶的公里数：%.2lf\n", kilometers_per_liter);

  return 0;
} */
/* #include <float.h>
#include <stdio.h>
#include <string.h>

void func1() {
  char first_name[20], last_name[20];
  printf("Enter your first name and last name.\n");
  scanf("%s %s", first_name, last_name);
  printf("%s, %s", first_name, last_name);
}

void func2() {
  char name[20];
  printf("Enter your name.\n");
  scanf("%s", name);
  printf("\"%s\"\n", name);
  printf("\"%20s\"\n", name);
  printf("\"%-20s\"\n", name);
  printf("%*s\n", (int)strlen(name) + 3, name);
}

void func3() {
  double num;
  scanf("%lf", &num);
  printf("The input is %.1lf or %.1e.\n", num, num);
  printf("The input is % .3lf or %.3E.\n", num, num);
}

void func4() {
  char name[20];
  double num;
  printf("Enter your name and height.\n");
  scanf("%s %lf", name, &num);
  printf("%s, you are %lf feet tall.\n", name, num);
}

void func5() {
  double mbits, mbytes;
  printf("Enter your data.\n");
  scanf("%lf %lf", &mbits, &mbytes);
  printf(
      "At %.2lf megabits per second, a file of %.2lf megabytes downloads in "
      "%.2lf seconds.",
      mbits, mbytes, mbytes * 8.0 / mbits);
}

void func6() {
  char first_name[20], last_name[20];
  printf("Enter your name.\n");
  scanf("%s %s", first_name, last_name);
  printf("%s %s\n", first_name, last_name);
  printf("%-*llu %-*llu\n", (int)strlen(first_name), strlen(first_name),
         (int)strlen(last_name), strlen(last_name));
  putchar('\n');
  printf("%s %s\n", first_name, last_name);
  printf("%*llu %*llu\n", (int)strlen(first_name), strlen(first_name),
         (int)strlen(last_name), strlen(last_name));
}

void func7() {
  double num1 = 1.0 / 3.0;
  float num2 = 1.0 / 3.0;
  printf("%.6lf %.6f\n", num1, num2);
  printf("%.12lf %.12f\n", num1, num2);
  printf("%.16lf %.16f\n", num1, num2);
  printf("%d %d\n", FLT_DIG, DBL_DIG);
}

const float MILES_TO_KILOMETERS = 1.609;
const float GALLONS_TO_LITERS = 3.785;

void func8() {
  double miles, gallons;
  printf("Enter your miles and gallons.");
  scanf("%lf %lf", &miles, &gallons);
  printf("%.1lf\n", miles / gallons);
  printf("%.1lf\n", miles * MILES_TO_KILOMETERS / gallons * GALLONS_TO_LITERS);
}

int main() {
  func8();
  return 0;
}
 */
/* #include <stdio.h>
#define ADJUST 7.31
int main() {
  const double SCALE = 0.333;
  double shoe, foot;

  printf("Shoe size (men's)    foot length.\n");
  shoe = 3.0;
  while (shoe < 18.5) {
    foot = SCALE * shoe + ADJUST;
    printf("%10.1f %15.2f inches\n", shoe, foot);
    shoe = shoe + 1.0;
  }
  printf("If the shoe fits, wear it.\n");

  return 0;
} */
/* #include <stdio.h> */
/* int main() {
  int jane, tarzan, cheeta;

  cheeta = jane = tarzan = 68;
  printf("               cheeta  tarzan  jane\n");
  printf("First round score %4d %8d %8d\n", cheeta, tarzan, jane);

  return 0;
} */
/* int main() {
  int num = 1;

  while (num < 21) {
    printf("%4d %6d\n", num, num * num);
    num = num + 1;
  }

  return 0;
} */
/* int main() {
  float num1 = 3.14;
  int num2 = (int)num1;
  int y = 2;
  int n = 3;
  printf("%d\n", (y + n++) * 6);

  printf("%.2f\n", num1);
  printf("%d\n", num2);

  return 0;
} */
/* #include <stdio.h>
#define FORMAT "%s! C is cool!\n"
int main() {
  int num = 10;
  printf(FORMAT, FORMAT);
  return 0;
} */
/* #include <stdio.h>

int main() {
  char c1, c2;
  int diff;
  float num;

  c1 = 'S';
  c2 = 'O';
  diff = c1 - c2;
  num = diff;
  printf("%c%c%c:%d %3.2f\n", c1, c2, c1, diff, num);
  return 0;
} */
/* #include <stdio.h>

int main() {
  char ch = 'a' - 1;

  while (ch++ < 'z') printf("%5c", ch);
  printf("\n");
  return 0;
} */
/* #include <stdio.h>

const int M_TO_H_M = 60;

int main() {
  int m = 0;
  int h = 0;

  scanf("%d", &m);
  while (m > 0) {
    h = m / M_TO_H_M;
    m %= M_TO_H_M;
    printf("%d_%d\n", h, m);
    scanf("%d", &m);
  }

  return 0;
} */
/* #include <stdio.h>

int main() {
  int num = 0;
  printf("请输入一个整数：\n");
  scanf("%d", &num);
  for (int i = 0; i <= 10; ++i) {
    printf("%d ", num++);
  }
  return 0;
} */
/* int main() {
  int days = 0;
  int leaves = 0;
  int weeks = 0;
  printf("输入所求的天数：\n");
  scanf("%d", &days);
  while (days > 0) {
    weeks = days / 7;
    leaves = days % 7;
    printf("%d days are %d weeks, %d days.\n", days, weeks, leaves);
    printf("请继续输入所求值：\n");
    scanf("%d", &days);
  }
  printf("输入值不符，跳出循环。\n");
  return 0;
} */
/*
const float CM_TO_FEET = 30.48f;

int main() {
  int flag = 1;
  float centimeters = 0.0f;
  float feet = 0.0f;
  float inches = 0.0f;
  while (centimeters > 0.0 || flag) {
    flag = 0;
    printf("Enter a height in centimeters: ");
    scanf("%f", &centimeters);
    if (centimeters <= 0) break;
    feet = centimeters / CM_TO_FEET;
    inches = (feet - (int)feet) * 12;
    printf("%f cm = %d feet, %f inches\n", centimeters, (int)feet, inches);
  }
  return 0;
} */
/* int main() {
  int count = 0;
  int num = 0;
  int sum = 0;
  scanf("%d", &num);
  while (count++ < num) sum += count * count;
  printf("sum = %d\n", sum);
  return 0;
} */
/* double cube(double num) { return num * num * num; }
int main() {
  double num = 0.0;
  scanf("%lf", &num);
  printf("%lf", cube(num));
  return 0;
} */
/* int main() {
  int num1 = 0;
  int num2 = 0;

  printf("请输入第二个数：");
  scanf("%d", &num2);
  printf("请输入第一个数：");
  scanf("%d", &num1);

  while (num1 > 0) {
    printf("%d %% %d = %d\n", num1, num2, num1 % num2);
    printf("请输入第二个数：");
    scanf("%d", &num1);
  }
  printf("结束！\n");

  return 0;
} */
/* void ConvertTemp(double t1) {
  const double celsiusRatio = 5.0 / 9.0;
  const double fahrenheitOffset = 32.0;
  const double kelvinOffset = 273.16;

  double t2 = celsiusRatio * (t1 - fahrenheitOffset);
  double t3 = t2 + kelvinOffset;

  printf("%lf %lf\n", t2, t3);
}

int main() {
  double temperature = 0.0;

  while (scanf("%lf", &temperature) == 1) {
    ConvertTemp(temperature);
  }

  return 0;
}
 */