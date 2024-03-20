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
/* #include <ctype.h>
int main() {
  long num;
  long sum = 0L;
  int status;

  printf("Please enter an integer to be summed ");
  printf("(q to quit): ");
  status = scanf("%ld", &num);
  while (status == 1) {
    sum = sum + num;
    printf("Please enter next integer (q to quit): ");
    status = scanf("%ld", &num);
  }
  while (isalpha(getchar()))
    ;
  char ch = 0;
  scanf("%c", &ch);
  printf("%c\n", ch);
  printf("Those integers sum to %ld.\n", sum);

  return 0;
} */
/* int main() {
  int index = 1;
  while (index < 5)
    printf("Good morning!\n");
  return 0;
} */
/* #include <math.h>
#include <stdio.h>
int main() {
  const double ANSWER = 3.14159;
  double response;

  printf("What is the value of pi?\n");
  scanf("%lf", &response);
  while (fabs(response - ANSWER) > 0.0001) {
    printf("Try again!\n");
    scanf("%lf", &response);
  }
  printf("Close enough!\n");

  return 0;
} */
/* int main() {
  int num;

  printf("    n n cubed\n");
  for (num = 1; num <= 6; num++) {
    printf("%5d %5d\n", num, num * num * num);
  }

  return 0;
} */
/* int main() {
  int x = 0;
  x = (249, 500);
  printf("%d\n", x);
  return 0;
} */
/* int main() {
  int t_ct;
  double time, power_of_2;
  int limit;

  printf("Enter the number of terms you want: ");
  scanf("%d", &limit);
  for (time = 0, power_of_2 = 1, t_ct = 1; t_ct <= limit;
       t_ct++, power_of_2 *= 2.0) {
    time += 1.0 / power_of_2;
    printf("time = %f when terms = %d.\n", time, t_ct);
  }

  return 0;
} */
/* int main() {
  const int secret_code = 13;
  int code_entered;

  do {
    printf("To enter the triskaidekaphobia therapy club,\n");
    printf("please enter the secret code number: ");
    scanf("%d", &code_entered);
  } while (code_entered != secret_code);
  printf("Congratulations! You are cured!\n");

  return 0;
} */
/* #define ROWS 6
#define CHARS 10
int main() {
  int row;
  char ch;

  for (row = 0; row < ROWS; ++row) {
    for (ch = 'A'; ch < ('A' + CHARS); ch++) {
      printf("%c", ch);
    }
    printf("\n");
  }

  return 0;
} */
/* int main() {
  const int ROWS = 6;
  const int CHARS = 6;
  int row;
  char ch;

  for (row = 0; row < ROWS; row++) {
    for (ch = ('A' + row); ch < ('A' + CHARS); ++ch) {
      printf("%c", ch);
    }
    putchar('\n');
  }

  return 0;
} */
/* #define SIZE 10
#define PAR 72
int main() {
  int index, score[SIZE];
  int sum = 0;
  float average;

  printf("Enter %d golf scores:\n", SIZE);
  for (index = 0; index < SIZE; index++) {
    scanf("%d", &score[index]);
  }
  printf("The scores read in are as follows:\n");
  for (index = 0; index < SIZE; ++index) {
    printf("%5d", score[index]);
    sum += score[index];
  }
  printf("\n");
  average = (float)sum / SIZE;
  printf("Sum of scores = %d, average = %.2f\n", sum, average);
  printf("That's a handicap of %.0f.\n", average - PAR);

  return 0;
} */
/* double power(double, int);
int main() {
  double n;
  int p;
  scanf("%lf %d", &n, &p);
  printf("%lf", power(n, p));
  return 0;
}
double power(double n, int p) {
  double pow = 1.0;
  for (int i = 1; i <= p; ++i) {
    pow *= n;
  }
  return pow;
} */
/* int main() {
  float value = 0.0f;
  for (value = 36.0f; value > 0; value /= 2) {
    printf("%3d", value);
  }
  return 0;
} */
/* int main() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 8; ++j) {
      printf("$");
    }
    printf("\n");
  }
  return 0;
} */
/* int main() {
  char alpha[27] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < 26; ++i) {
    printf("%c", alpha[i]);
  }
  putchar('\n');
  return 0;
} */
/* int main() {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j <= i; ++j) {
      printf("$");
    }
    printf("\n");
  }
  return 0;
} */
/* int main() {
  char lets[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 4 - i; ++j) {
      printf(" ");
    }
    for (int j = 0; j <= i; ++j) {
      printf("%c", lets[j]);
    }
    for (int j = i - 1; j >= 0; --j) {
      printf("%c", lets[j]);
    }
    printf("\n");
  }
  return 0;
} */
/* int main() {
  int low, high;
  printf("输入上限和下限：\n");
  scanf("%d %d", &low, &high);
  for (int i = low; i <= high; ++i) {
    printf("%d\t%d\t%d\n", i, i * i, i * i * i);
  }
  return 0;
} */
/* int main() {
  char str[20];
  scanf("%s", str);
  int len = strlen(str);
  for (int i = len - 1; i >= 0; --i) {
    printf("%c", str[i]);
  }
  putchar('\n');
  return 0;
}
 */
/* double func(double n1, double n2) { return (n1 - n2) / (n1 * n2); }
int main() {
  float n1 = 0.0f;
  float n2 = 0.0f;
  while (scanf("%f %f", &n1, &n2) == 2) {
    printf("%f\n", func(n1, n2));
  }
  return 0;
} */
/* int main() {
  int low, high;
  while (scanf("%d %d", &low, &high) == 2) {
    if (low >= high) {
      break;
    }
    long long sum = 0;  // 使用 long long 类型来避免整数溢出
    for (int i = low; i <= high; ++i) {
      sum += (long long)i * i;  // 将 i 先转换为 long long 类型再进行运算
    }
    printf("%lld\n", sum);  // 输出长整型数据
  }
  return 0;
} */
/* int main() {
  int arr[8];
  for (int i = 0; i < 8; ++i) {
    scanf("%d", &arr[i]);
  }
  for (int i = 7; i >= 0; --i) {
    printf("%d ", arr[i]);
  }
  return 0;
} */
/* int main() {
  long double sum1 = 0.0;
  long double sum2 = 0.0;

  for (int i = 1; i <= 99; ++i) {  // 对于sum1, 我们从1累加到99（包括99）
    sum1 += 1.0 / (long double)i;  // 使用 long double 类型进行计算
  }

  printf("Sum1: %Lf\n", sum1);

  long double pow = 1.0;

  for (int i = 1; i < 100;
       ++i) {  // 对于sum2, 我们仍从1累加到99，但pow在循环中改变
    sum2 += pow / (long double)i;
    pow *= -1.0;  // 将-1改为-1.0，确保乘法后为浮点数
  }

  printf("Sum2: %Lf\n", sum2);

  return 0;
} */
/* int main() {
  int arr[8];
  for (int i = 0; i < 8; ++i) {
    arr[i] = pow(2, i);
  }
  int i = 0;
  do {
    printf("%d ", arr[i]);
    ++i;
  } while (i < 8);
  return 0;
} */
/* int main() {
  double arr1[8], arr2[8];
  for (int i = 0; i < 8; ++i) {
    scanf("%lf", &arr1[i]);
    arr2[i] = (i > 0) ? arr1[i] + arr2[i - 1] : arr1[i];
  }
  for (int i = 0; i < 8; ++i) {
    printf("%lf ", arr2[i]);
  }
  printf("\n");
  return 0;
} */
/* int main() {
  char str[256] = {0};
  fgets(str, 256, stdin);
  int len = strlen(str);
  str[len - 1] = '\0';
  for (int i = len - 1; i >= 0; --i) {
    putchar(str[i]);
  }
  return 0;
} */
/* int main() {
  double a = 100.0;
  double b = 100.0;
  int year = 0;
  while (a >= b) {
    a += 10;
    b += b * 0.05;
    ++year;
  }
  printf("%d\n", year);
  printf("%lf %lf\n", a, b);
  return 0;
} */
/* int main() {
  double money = 1e6;
  int year = 0;
  while(money > 0.0) {
    money = money * 0.08 - 10;
    ++year;
  }
  printf("%d\n", year);
  return 0;
} */
/* int main() {
  const int MAX = 150;
  int friends = 5;
  for (int i = 1;; ++i) {
    friends -= i;
    friends *= 2;
    if (friends > MAX) break;
    printf("第 %d 周的朋友数量为 %d。\n", i, friends);
  }
  return 0;
} */
/* #define SPACE ' '
int main() {
  char ch;
  while ((ch = getchar()) != '\n') {
    if (ch == SPACE) {
      putchar(ch);
    } else {
      putchar(ch + 1);
    }
  }
  putchar(ch);
  return 0;
} */
/* int main() {
  unsigned long num;
  unsigned long div;
  bool isPrime;

  printf("Please enter an integer for analysis; ");
  printf("Enter q to quit.\n");
  while (scanf("%lu", &num) == 1) {
    for (div = 2, isPrime = true; (div * div) <= num; ++div) {
      if (num % div == 0) {
        if (div * div != num) {
          printf("%lu is divisiable by %lu and %lu.\n", num, div, num / div);
        } else {
          printf("%lu is divisible by %lu.\n", num, div);
        }
        isPrime = false;
      }
    }
    if (isPrime) {
      printf("%lu is prime.\n", num);
    }
    printf("Please enter another integer for analysis; ");
    printf("Enter q to quit.\n");
  }
  printf("Bye.\n");

  return 0;
} */
/* #define PERIOD '.'
int main() {
  char ch;
  int charcount = 0;

  while ((ch = getchar()) not_eq PERIOD) {
    if (ch not_eq '"' and ch not_eq '\'') charcount++;
  }
  printf("There are %d non-quote characters.\n", charcount);

  return 0;
} */
/* #include <stdio.h>
int main() {
  char ch;
  int a_ct, e_ct, i_ct, o_ct, u_ct;

  a_ct = e_ct = i_ct = o_ct = u_ct = 0;
  printf("Enter some text; enter # to quit.\n");
  while ((ch = getchar()) != '#') {
    switch (ch) {
      case 'a':
      case 'A':
        a_ct++;
        break;
    }
  }
}
 */
/* #include <stdio.h>
int main() {
  char ch;

  while ((ch = getchar()) != '#') {
    if (ch == '\n') {
      continue;
    }
    printf("Step 1\n");
    if (ch == 'c') {
      continue;
    } else if (ch == 'b') {
      break;
    } else if (ch == 'h') {
      goto laststep;
    }
    printf("Step 2\n");
  laststep:
    printf("Step 3\n");
  }
  printf("Done\n");
  return 0;
} */
/* #include <stdio.h>
int main() {
  char ch;
  while ((ch = getchar()) != '#') {
    if (ch != '\n') {
      printf("Step 1\n");
      if (ch != 'c') {
        if (ch == 'b') {
          break;
        } else if (ch == 'h') {
          printf("Step 3\n");
        } else {
          printf("Step 2\n");
          printf("Step 3\n");
        }
      }
    }
  }
} */
/* #include <stdio.h>
int main() {
  int a_t = 0;
  int b_t = 0;
  int c_t = 0;
  char ch = 0;
  while ((ch = getchar()) != '#') {
    if (ch == ' ') {
      ++a_t;
    } else if (ch == '\n') {
      ++b_t;
    } else {
      ++c_t;
    }
  }
  printf("%d %d %d\n", a_t, b_t, c_t);
  return 0;
} */
/* #include <stdio.h>
#include <string.h>
int main() {
  int i = 0;
  char ch = 0;
  char str[160] = {0};
  for (i = 0; (ch = getchar()) != '#'; ++i) {
    if (ch != '#') str[i] = ch;
  }
  str[i] = '\0';
  for (int i = 0; i < strlen(str); ++i) {
    if (str[i] != '\n') {
      printf("%c-%d\t", str[i], str[i]);
    } else {
      printf("\\n-%d\t", str[i]);
    }
    if ((i + 1) % 8 == 0) {
      putchar('\n');
    }
  }
  return 0;
} */
/* #include <stdbool.h>
#include <stdio.h>

int main() {
  int num = 0;
  int a_sum = 0;
  int b_sum = 0;
  int a_count = 0;
  int b_count = 0;
  while (true) {
    scanf("%d", &num);
    if (num == 0) break;
    if (num % 2 == 0) {
      a_count++;
      a_sum += num;
    } else {
      b_count++;
      b_sum += num;
    }
  }
  if (a_count == 0 || b_count == 0) return 1;
  printf("%d %lf %d %lf\n", a_count, (double)a_sum / a_count, b_count,
         (double)b_sum / b_count);
  return 0;
} */
/* int main() {
  int i = 0;
  char ch;
  char str[100];
  while ((ch = getchar()) != '#') {
    if (ch == '.') {
      str[i] = '!';
      ++i;
    } else if (ch == '!') {
      str[i] = ch;
      str[i + 1] = ch;
      i += 2;
    } else {
      str[i] = ch;
      ++i;
    }
  }
  str[i] = '#';
  for (i = 0; str[i] != '#'; ++i) {
    putchar(str[i]);
  }
  return 0;
} */
/* #include <stdio.h>
int main() {
  int i = 0;
  char ch;
  char str[100];
  while ((ch = getchar()) != '#') {
    switch (ch) {
      case '.':
        str[i] = '!';
        ++i;
        break;
      case '!':
        str[i] = ch;
        str[i + 1] = ch;
        i += 2;
        break;
      default:
        str[i] = ch;
        ++i;
        break;
    }
  }
  str[i] = '#';
  for (i = 0; str[i] != '#'; ++i) {
    putchar(str[i]);
  }
  return 0;
} */
/* #include <stdio.h>
#define BASEPAY 10
#define BASEHRS 40
#define OVERTIME 1.5
#define AMT1 300
#define AMT2 150
#define RATE1 0.15
#define RATE2 0.20
#define RATE3 0.25
int main() {
  double hours;
  double gross;
  double net;
  double taxes;

  printf("Enter the number of hours worked this week: ");
  scanf("%lf", &hours);
  if (hours <= BASEHRS) {
    gross = hours * BASEPAY;
  } else {
    gross = BASEHRS * BASEPAY + (hours - BASEHRS) * BASEPAY * OVERTIME;
  }
  if (gross <= AMT1) {
    taxes = gross * RATE1;
  } else if (gross <= AMT1 + AMT2) {
    taxes = AMT1 * RATE1 + (gross - AMT1) * RATE2;
  } else {
    taxes = AMT1 * RATE1 + AMT2 * RATE2 + (gross - AMT1 - AMT2) * RATE3;
  }
  net = gross - taxes;
  printf("gross: $%.2f; taxes: $%.2f; net: $%.2f\n", gross, taxes, net);

  return 0;
} */
/* #include <stdio.h>
int isPrime(int num) {
  for (int div = 2; div * div <= num; ++div) {
    if (num % div == 0) return 0;
  }
  return 1;
}
int main() {
  int num;
  scanf("%d", &num);
  for (int i = 2; i <= num; ++i) {
    if (isPrime(i)) printf("%d ", i);
  }
  return 0;
} */
/* #include <stdio.h>
int main() {
  int num;
  float tax;
  char ch;
  while (scanf("%c %d", &ch, &num) == 2) {
    switch (ch) {
      case 'a':
        if (num < 17850) {
          tax = num * 0.15;
        } else {
          tax = 17850 * 0.15 + (num - 17850) * 0.28;
        }
        break;
      case 'b':
        if (num < 23900) {
          tax = num * 0.15;
        } else {
          tax = 23900 * 0.15 + (num - 23900) * 0.28;
        }
        break;
      case 'c':
        if (num < 29750) {
          tax = num * 0.15;
        } else {
          tax = 29750 * 0.15 + (num - 29750) * 0.28;
        }
        break;
      case 'd':
        if (num < 14875) {
          tax = num * 0.15;
        } else {
          tax = 14875 * 0.15 + (num - 14875) * 0.28;
        }
        break;
    }
    printf("%d %f\n", num, tax);
    while (getchar() != '\n') continue;
  }
  return 0;
}
 */
/* #include <stdio.h>

double calculateInitialCost(int weight, double value) {
  double sum = weight * value;
  if (sum > 100) {
    sum -= sum * 0.05;
  }
  return sum;
}

double calculateAdditionalCost(int weight, double sum) {
  if (weight <= 5) {
    sum += 6.5;
  } else if (weight > 5 && weight <= 20) {
    sum += 14;
  } else {
    sum += 14 + (weight - 20) * 0.5;
  }
  return sum;
}

int main() {
  char option;
  double weight = 0.0;
  double temp;
3
  // Read the option
  scanf(" %c", &option);

  // Read weights until user input ends
  while (scanf("%lf", &temp) == 1) {
    weight += temp;
  }

  printf("Total weight: %lf\n", weight);

  switch (option) {
    case 'a':
      printf(
          "Initial Cost: %lf, Total Cost: %lf\n",
          calculateInitialCost(weight, 2.05),
          calculateAdditionalCost(weight, calculateInitialCost(weight, 2.05)));
      break;
    case 'b':
      printf(
          "Initial Cost: %lf, Total Cost: %lf\n",
          calculateInitialCost(weight, 1.15),
          calculateAdditionalCost(weight, calculateInitialCost(weight, 1.15)));
      break;
    case 'c':
      printf(
          "Initial Cost: %lf, Total Cost: %lf\n",
          calculateInitialCost(weight, 1.09),
          calculateAdditionalCost(weight, calculateInitialCost(weight, 1.09)));
      break;
    default:
      printf("Invalid option\n");
  }

  return 0;
} */
/* #include <stdio.h>

int main() {
  int ch;
  while ((ch = getchar()) != EOF) {
    putchar(ch);
  }
  return 0;
} */
#include <stdio.h>

void up_and_down(int);

int main() {
  up_and_down(1);
  return 0;
}

void up_and_down(int n) {
  printf("Level %d: n location %p\n", n, &n);
  if (n < 4) {
    up_and_down(n + 1);
  }
  printf("LEVEL %d: n location %p\n", n, &n);
}