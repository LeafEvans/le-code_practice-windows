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
/* #include <stdio.h>

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
} */
/* #include <stdio.h>
#define MONTHS 12
int main() {
  int days[MONTHS] = {31, 28, [4] = 31, 30, 31, [1] = 29};
  int i;
  for (i = 0; i < MONTHS; ++i) {
    printf("%2d  %d\n", i + 1, days[i]);
  }
  return 0;
} */
/* #include <stdio.h>
#define SIZE 4
int main() {
  int value1 = 44;
  int arr[SIZE];
  int value2 = 88;
  int i;

  printf("value1 = %d, value2 = %d\n", value1, value2);
  for (i = -1; i <= SIZE; ++i) {
    arr[i] = 2 * i + 1;
  }

  for (i = -1; i < 7; ++i) {
    printf("%2d %d\n", i, arr[i]);
  }
  printf("value1 = %d, value2 = %d\n", value1, value2);
  printf("address of arr[-1]: %p\n", &arr[-1]);
  printf("address of arr[4]: %p\n", &arr[4]);
  printf("address of value1: %p\n", &value1);
  printf("address of value2: %p\n", &value2);

  return 0;
} */
/* #define SIZE 4
int main() {
  short dates[SIZE];
  short* pti;
  short index;
  double bills[SIZE];
  double* ptf;
  pti = dates;
  ptf = bills;
  printf("%23s %10s\n", "short", "double");
  for (index = 0; index < SIZE; ++index) {
    printf("pointers + %d: %10p %10p\n", index, pti + index, ptf + index);
  }
  return 0;
} */
/* #include <stdio.h>
#define MONTHS 12

int main() {
  int days[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int index;

  for (index = 0; index < MONTHS; ++index) {
    printf("Month %2d has %d days.\n", index + 1, *(days + index));
  }

  return 0;
} */
/* #include <stdio.h>
#define SIZE 10
int sump(int *, int *);
int main() {
  int marbles[SIZE] = {20, 10, 5, 39, 4, 16, 19, 26, 31, 20};
  long answer;

  answer = sump(marbles, marbles + SIZE);
  printf("The total number of marbles is %ld.\n", answer);

  return 0;
}

int sump(int *start, int *end) {
  int total = 0;

  while (start < end) {
    total += *start++;
  }

  return total;
} */
/* #include <stdio.h>
#define SIZE 5
void show_array(const double[], int);
void mult_array(double[], int, double);
int main() {
  double dip[SIZE] = {20.0, 17.66, 8.2, 15.3, 22.22};
  printf("The original dip array:\n");
  show_array(dip, SIZE);
  mult_array(dip, SIZE, 2.5);
  printf("The dip array calling mult_array():\n");
  show_array(dip, SIZE);

  return 0;
}

void show_array(const double ar[], int n) {
  int i;

  for (i = 0; i < n; ++i) {
    printf("%8.3f ", ar[i]);
  }
  putchar('\n');
}

void mult_array(double ar[], int n, double mult) {
  int i;

  for (i = 0; i < n; ++i) {
    ar[i] *= mult;
  }
} */
/* #include <stdio.h>
#define ROWS 3
#define COLS 4
int sum2d(int, int, int ar[*][*]);
int main() {
  int rs = 3;
  int cs = 10;
  int junk[ROWS][COLS] = {{2, 4, 6, 8}, {3, 5, 7, 9}, {12, 10, 8, 6}};

  int morejunk[ROWS - 1][COLS + 2] = {{20, 30, 40, 50, 60, 70},
                                      {5, 6, 7, 8, 9, 10}};

  int varr[rs][cs];

  for (int i = 0; i < rs; ++i) {
    for (int j = 0; j < cs; ++j) {
      varr[i][j] = i * j + j;
    }
  }

  printf("3x4 array\n");
  printf("Sum of all elements = %d\n", sum2d(ROWS, COLS, junk));

  printf("2x6 array\n");
  printf("Sum of all elements = %d\n", sum2d(ROWS - 1, COLS + 2, morejunk));

  printf("3x10 VLA\n");
  printf("Sum of all elements = %d\n", sum2d(rs, cs, varr));

  return 0;
}

int sum2d(int rows, int cols, int ar[rows][cols]) {
  int tot = 0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      tot += ar[r][c];
    }
  }

  return tot;
}
 */
/* #include <stdio.h>
#define COLS 4
int sum2d(const int ar[][COLS], int rows);
int sum(const int ar[], int n);
int main() {
  int total1, total2, total3;
  int *pt1;
  int(*pt2)[COLS];

  pt1 = (int[2]){10, 20};
  pt2 = (int[2][COLS]){{1, 2, 3, -9}, {4, 5, 6, -8}};
  total1 = sum(pt1, 2);
  total2 = sum2d(pt2, 2);
  total3 = sum((int[]){4, 4, 4, 5, 5, 5}, 6);
  printf("total1 = %d\n", total1);
  printf("total2 = %d\n", total2);
  printf("total3 = %d\n", total3);

  return 0;
}

int sum(const int ar[], int n) {
  int total = 0;

  for (int i = 0; i < n; ++i) {
    total += ar[i];
  }

  return total;
}

int sum2d(const int ar[][COLS], int rows) {
  int tot = 0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < COLS; ++c) {
      tot += ar[r][c];
    }
  }

  return tot;
} */
/*
void copy_arr(double[], double[], int);
void copy_ptr(double *, double *, int);
void copy_ptrs(double *, double *, double *);

int main() {
  double source[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
  double target1[5];
  double target2[5];
  double target3[5];
  copy_arr(target1, source, 5);
  copy_ptr(target2, source, 5);
  copy_ptrs(target3, source, source + 5);
  return 0;
}

void copy_arr(double target[], double source[], int n) {
  for (int i = 0; i < n; ++i) {
    target[i] = source[i];
  }
}

void copy_ptr(double *target, double *source, int n) {
  for (int i = 0; i < n; ++i) {
    *(target + i) = *(source + i);
  }
}

void copy_ptrs(double *target, double *source, double *end) {
  while (source != end) {
    *source++ = *target++;
  }
} */
/* #include <limits.h>
#include <stdio.h>

int max(int arr[], int n) {
  int max = INT_MIN;
  for (int i = 0; i < n; ++i) {
    if (arr[i] > max) max = arr[i];
  }

  return max;
}

int main() {
  int arr[10] = {1, 23, 423, 32, 32, 3, 232, 3, 32, 3};
  printf("%d\n", max(arr, sizeof(arr) / sizeof(int)));
  return 0;
} */
/* int min(double arr[], int n) {
  int index_min = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[index_min] > arr[i]) index_min = i;
  }
  return index_min;
}
int main() {
  double arr[10]={3,1,-2,3,4,5,6,7,8,9};
  printf("%d\n", min(arr, sizeof(arr)/sizeof(double)));
  return 0;
} */
/* #include <float.h>
#include <stdio.h>


double difference(double arr[], int n);

int main() {
  double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  int n = sizeof(arr) / sizeof(arr[0]);
  double diff = difference(arr, n);
  printf("Difference: %.2f\n", diff);
  return 0;
}

double difference(double arr[], int n) {
  double max = DBL_MIN;
  double min = DBL_MAX;

  for (int i = 0; i < n; ++i) {
    if (arr[i] > max) max = arr[i];
    if (arr[i] < min) min = arr[i];
  }

  return max - min;
}
 */
/* #include <stdio.h>
void inverse_arr(double arr[], int n) {
  for (int i = 0; i < n / 2; ++i) {
    double temp = arr[i];
    arr[i] = arr[n - i - 1];
    arr[n - i - 1] = temp;
  }
}
int main() {
  double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Original array: ");
  for (int i = 0; i < n; ++i) {
    printf("%.1f ", arr[i]);
  }
  printf("\n");

  inverse_arr(arr, n);

  printf("Inversed array: ");
  for (int i = 0; i < n; ++i) {
    printf("%.1f ", arr[i]);
  }
  printf("\n");

  return 0;
} */
/* int main() {
  double arr[2][5] = {{12, 2, 3, 35, 5}, {5, 90, 34, 2, 12}};
  double arr_new[2][5];
  for (int i = 0; i < 2; ++i) {
    copy_arr(arr_new[i], arr[i], 5);
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 5; ++j) {
      printf("%lf ", arr_new[i][j]);
    }
    printf("\n");
  }
  return 0;
} */
/* #include <stdio.h>
void copy_arr(double target[], double source[], int n) {
  for (int i = 0; i < n; ++i) {
    target[i] = source[i];
  }
}
int main() {
  double arr1[7] = {9, 2, 3, 4, 1, 2, 3};
  double arr2[3];

  copy_arr(arr2, arr1 + 2, 3);
  for (int i = 0; i < 3; ++i) {
    printf("%f ", arr2[i]);
  }
  printf("\n");
  return 0;
} */
/* #include <stdio.h>
void copy_arr(int, int, double[*][*], double[*][*]);
void show_arr(int, int, double[*][*]);
int main() {
  double arr1[3][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}};
  double arr2[3][5];

  copy_arr(3, 5, arr2, arr1);
  show_arr(3, 5, arr2);

  return 0;
}

void copy_arr(int row, int col, double des[row][col], double src[row][col]) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      des[i][j] = src[i][j];
    }
  }
}

void show_arr(int row, int col, double arr[row][col]) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      printf("%lf ", arr[i][j]);
    }
    printf("\n");
  }
} */
/* #include <stdio.h>
void add_arr(int *arr1, int *arr2, int *arr3, int n) {
  for (int i = 0; i < n; ++i) {
    arr3[i] = arr1[i] + arr2[i];
  }
}
int main() {
  int arr1[4] = {2, 4, 5, 8};
  int arr2[4] = {1, 0, 4, 6};
  int arr3[4];
  add_arr(arr1, arr2, arr3, 4);
  for (int i = 0; i < 4; ++i) printf("%d ", arr3[i]);
  return 0;
} */
/* #include <stdio.h>

void pow_2(int arr[][5], int row) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < 5; ++j) {
      arr[i][j] *= 2;
    }
  }
}

void show(int arr[][5], int row) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < 5; ++j) {
      printf("%2d ", arr[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int arr[3][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}};
  show(arr, 3);
  pow_2(arr, 3);
  show(arr, 3);
  return 0;
} */
/* #include <float.h>
#include <stdio.h>

void get_data(int row, int col, double arr[row][col]) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      scanf("%lf", &arr[i][j]);
    }
  }
}
double average(double arr[], int n) {
  double total = 0;
  for (int i = 0; i < n; ++i) {
    total += arr[i];
  }
  return total / n;
}
double average_total(int row, int col, double arr[row][col]) {
  double total = 0;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      total += arr[i][j];
    }
  }
  return total / (row * 5);
}
double max(int row, int col, double arr[row][col]) {
  double max = DBL_MIN;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (max < arr[i][j]) max = arr[i][j];
    }
  }
  return max;
}
void show_arr(int row, int col, double arr[row][col]) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      printf("%lf ", arr[i][j]);
    }
    printf("\n");
  }
}
int main() {
  double arr[3][5];
  get_data(3, 5, arr);
  show_arr(3, 5, arr);
  for (int i = 0; i < 3; ++i) {
    printf("%lf ", average(arr[i], 5));
  }
  printf("\n");
  printf("%lf\n", average_total(3, 5, arr));
  printf("%lf\n", max(3, 5, arr));
  return 0;
} */
/* #include <stdio.h>
#define MSG "I am a symbolic string constant."
#define MAXLENGTH 81

int main() {
  char words[MAXLENGTH] = "I am a string in an array.";
  const char* pt1 = "Something is pointing at me.";
  puts("Hero are some strings:");
  puts(MSG);
  puts(words);
  puts(pt1);
  words[8] = 'p';
  puts(words);

  return 0;
} */
/* #include <stdio.h>

int main() {
  printf("%s, %p, %c\n", "We", "are", *"space farers");
  return 0;
} */
/* #define MSG "I'm special"

#include <stdio.h>

int main() {
  char ar[] = MSG;
  const char *pt = MSG;

  printf("address of \"I'm special\": %p \n", "I'm special");
  printf("            address ar: %p\n", ar);
  printf("            address pt: %p\n", pt);
  printf("        address of MSG: %p\n", MSG);
  printf("address of \"I'm special\": %p \n","I'm special");

  return 0;
} */
/* #include <stdio.h>

int main() {
  char *p1 = "Klingon";
  p1[0] = 'F';
  printf("Klingon");
  printf(": Beware the %ss!\n", "Klingon");
  return 0;
} */
/* #include <stdio.h>
#define SLEN 40
#define LIM 5
int main() {
  const char *mytalents[LIM] = {
      "Adding numbers swiftly", "Multiplying accurately", "Stashing data",
      "Following instructions to the letter", "Understanding the C language"};

  char yourtalents[LIM][SLEN] = {"Walking in straight line", "Sleeping",
                                 "Watching television", "Mailing letters",
                                 "Reading email"};

  puts("Let's compare talents.");
  printf("%-36s  %-25s\n", "My Talents", "Your Talents");
  for (int i = 0; i < LIM; ++i) {
    printf("%-36s  %-25s\n", mytalents[i], yourtalents[i]);
  }
  printf("\nsizeof mytalents: %zd, sizeof yourtalents: %zd\n",
         sizeof(mytalents), sizeof(yourtalents));

  return 0;
} */
/* #include <stdio.h>
#define STLEN 5
int main() {
  char words[STLEN];

  puts("Enter a string, please.");
  gets(words);
  printf("Your string twice:\n");
  printf("%s\n", words);
  puts(words);
  puts("Done.");

  return 0;
} */
/* #include <stdio.h>
#define STLEN 14
int main() {
  char words[STLEN];

  puts("Enter a string, please.");
  fgets(words, STLEN, stdin);
  printf("Your string twice (puts(), then fputs()):\n");
  puts(words);
  fputs(words, stdout);
  puts("Enter another string, please.");
  fgets(words, STLEN, stdin);
  printf("Your string twice (puts(), then fputs()):\n");
  puts(words);
  fputs(words, stdout);
  puts("Done.");

  return 0;
} */
/* #include <stdio.h>
#define STLEN 10
int main() {
  char words[STLEN];

  puts("Enter strings (empty line to quit):");
  while (fgets(words, STLEN, stdin) != NULL && words[0] != '\n') {
    fputs(words, stdout);
  }
  puts("Done.");
  return 0;
} */
/* #include <stdio.h>
#define STLEN 10
int main() {
  char words[STLEN];  // 存储字符串的数组
  int i;              // 循环变量

  puts("Enter strings (empty line to quit):");  // 提示语句
  // 如果到达文件末尾或者输入的第一个字符为 '\0'
  while (fgets(words, STLEN, stdin) != NULL && words[0] != '\n') {
    i = 0;
    // 如果不是换行符或者结束字符，循环变量就加 1
    while (words[i] != '\n' && words[i] != '\0') {
      // 搞到字符串末尾
      ++i;
    }
    // 如果最后一个字符是换行符，就替换为空字符
    // 换行符说明输入的字符串存的下去
    if (words[i] == '\n') {
      words[i] = '\0';
    } else {
      // 如果不是，说明输入的字符存不下去
      // 把还在缓冲区的全部清除
      while (getchar() != '\n') {
        continue;
      }
    }
    // 输出
    puts(words);
  }
  puts("done");
  return 0;
} */
/* #include <stdio.h>

int main() {
  char str[21] = {0};
  gets_s(str, 21);
  puts(str);
  return 0;
} */
/* #include <stdio.h>
char *s_gets(char *st, int n) {
  // 数组
  char *ret_val;
  int i = 0;

  // 输入字符串
  ret_val = fgets(st, n, stdin);

  // 如果不为空指针
  if (ret_val) {
    // 如果不为换行符或者空字符
    while (st[i] != '\n' && st[i] != '\0') {
      ++i;  // 字符下标加 1
    }
    // 如果是换行符，就改为 0
    if (st[i] == '\n') {
      st[i] = '\0';
    } else {
      // 不是，说明超了
      // 清空缓冲区
      while (getchar() != '\n') {
        continue;
      }
    }
  }
  return ret_val;
} */
/* #include <stdio.h>
int main() {
  char name1[11], name2[11];
  int count;

  printf("Please enter 2 names\n");
  count = scanf("%5s %10s", name1, name2);
  printf("I read the %d names %s and %s.\n", count, name1, name2);

  return 0;
} */
/* #include <stdio.h>
int main() {
  char side_a[] = "Side A";
  char dont[] = {'W', 'O', 'W', '!'};
  char side_b[] = "Side B";

  puts(dont);

  return 0;
} */
/* #include <stdio.h>
void put1(const char *string) {
  while (*string != '\0') {
    putchar(*string++);
  }
} */
/* #include <stdio.h>

void put1(const char *);
int put2(const char *);

int main() {
  put1("If I'd as much money");
  put2(" as I could spend,\n");
  printf("I count %d characters.\n",
         put2("I never would cry old chairs to mend."));
  return 0;
}

void put1(const char *string) {
  while (*string) {
    putchar(*string++);
  }
}

int put2(const char *string) {
  int count = 0;
  while (*string) {
    putchar(*string++);
    ++count;
  }
  putchar('\n');

  return count;
} */
/* #include <stdio.h>
#include <string.h>
void fit(char *, unsigned int);

int main() {
  char mesg[] = "Thing should be as simple as possible but not simpler.";

  puts(mesg);
  fit(mesg, 38);
  puts(mesg);
  puts("Let's look at some more of the string.");
  puts(mesg + 39);

  return 0;
}

void fit(char *string, unsigned int size) {
  if (strlen(string) > size) {
    string[size] = '\0';
  }
} */
/* int main() {
  char flower[SIZE];
  char addon[] = "s small like old shoes.";
  puts("What is your favorite flowers?");
  if (s_gets(flower, SIZE)) {
    strcat(flower, addon);
    puts(flower);
    puts(addon);
  } else {
    puts("End of file encountered!");
  }
  puts("bye");

  return 0;
} */
/* #include <stdio.h>
#include <string.h>
#define SIZE 30
#define BUGSIZE 13
char *s_gets(char *, int);

int main() {
  // 花的数组
  char flower[SIZE];
  // 插件的意思
  char addon[] = "s small like old shoes.";
  // 蛾子数组
  char bug[BUGSIZE];
  // 可用的长度
  int available;
  // 最喜欢啥花
  puts("What is your favourite flower?");
  s_gets(flower, SIZE);
  // 如果小于指定的大小
  // 使用 strlen
  if ((strlen(addon) + strlen(flower) + 1) <= SIZE) {
    // 拼接
    strcat(flower, addon);
  }
  // 输出花朵
  puts(flower);
  // 你最喜欢的蛾子是什么
  puts("What is your favorite bug?");
  s_gets(bug, BUGSIZE);
  // 还要放空字符，所有 -1
  available = BUGSIZE - strlen(bug) - 1;
  // 可用的就这么多
  // 输入
  strncat(bug, addon, available);
  puts(bug);

  return 0;
} */
/* #include <stdio.h>
#include <string.h>

#define ANSWER "Grant"
#define SIZE 40

char *s_gets(char *, int);

int main() {
  char try[SIZE];

  puts("Who is buried in Grant's tomb?");
  s_gets(try, SIZE);
  while (strcmp(try, ANSWER) != 0) {
    puts("No, that's wrong. Try again.");
    s_gets(try, SIZE);
  }
  puts("That's right!");

  return 0;
} */
/* int main() {
  char input[LIM][SIZE];
  int ct = 0;

  printf("Enter up to %d lines (type quit to quit):\n", LIM);
  while (ct < LIM && s_gets(input[ct], SIZE) != NULL &&
         strcmp(input[ct], STOP) != 0) {
    ++ct;
  }
  printf("%d strings entered\n", ct);

  return 0;
} */
/* #include <stdio.h>
#include <string.h>
#define LITESIZE 6

int main() {
  const char *list[LITESIZE] = {"astronmy",  "astounding", "astrophysics",
                                "ostracize", "asterism",   "astrophobia"};
  int count = 0;

  for (int i = 0; i < LITESIZE; ++i) {
    if (!strncmp(list[i], "astro", 5)) {
      printf("Found: %s\n", list[i]);
      ++count;
    }
  }
  printf("The list contained %d words beginning with astro.\n", count);

  return 0;
} */
/* #include <stdio.h>
#include <string.h>
#define WORDS "beast"
#define SIZE 40

int main() {
  const char * orig = WORDS;
  char copy[SIZE] = "Be the best that you can be.";
  char *ps;

  puts(orig);
  puts(copy);
  ps = (strcpy(copy + 7, orig));
  puts(copy);
  puts(ps);
  puts(copy + 13);

  return 0;
} */
/* int main() {
  char qwords[LIM][SIZE];
  char temp[SIZE];

  int i = 0;
  while (i < LIM && s_gets(temp, SIZE)) {
    if (temp[0] != 'q') {
      printf("%s doesn't begin with q!\n", temp);
    } else {
      strcpy(qwords[i], temp);
      ++i;
    }
  }
  puts("Here are the words accepted:");
  for (i = 0; i < LIM; ++i) {
    puts(qwords[i]);
  }

  return 0;
} */
/* #include <stdio.h>
#include <string.h>
#define MAX 20
char *s_gets(char *, int);

int main() {
  char first[MAX];
  char last[MAX];
  char formal[2 * MAX + 10];
  double prize;

  puts("Enter your first name:");
  s_gets(first, MAX);
  puts("Enter your last name:");
  s_gets(last, MAX);
  puts("Enter your prize money:");
  scanf("%lf", &prize);
  sprintf(formal, "%s, %-19s: $%6.2f\n", last, first, prize);
  puts(formal);
  return 0;
}

char *s_gets(char *st, int n) {
  char *ret_val;
  int i = 0;

  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    while (st[i] != '\n' && st[i] != '\0') {
      ++i;
    }
    if (st[i] == '\n') {
      st[i] = '\0';
    } else {
      while (getchar() != '\n') {
        continue;
      }
    }
  }
  return ret_val;
} */
/* #include <stdio.h>
#include <string.h>

int main() {
  char str1[20] = "Hello World!";
  char str2[20] = "d";
  printf("%lld\n", strpbrk(str1, str2) - str1);
  return 0;
} */
/* #include <stdio.h>
#include <string.h>

int main() {
  char line[80];
  char *find;

  fgets(line, 80, stdin);
  *strchr(line, '\n') = '\0';
  printf("%s\n", line);
  return 0;
} */
/* #include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LIMIT 81
void ToUpper(char *);
int PunctCount(const char *);

int main() {
  char line[LIMIT];
  char *find;

  puts("Please enter a line:");
  fgets(line, LIMIT, stdin);
  find = strchr(line, '\n');
  if (find) *find = '\0';
  ToUpper(line);
  puts(line);
  printf("That line has %d punctuation characters.\n", PunctCount(line));

  return 0;
}

void ToUpper(char *str) {
  while (*str) {
    *str = toupper(*str);
    ++str;
  }
}

int PunctCount(const char *str) {
  int ct = 0;
  while (*str) {
    if (ispunct(*str)) {
      ++ct;
    }
    ++str;
  }

  return ct;
} */
/* #include <stdio.h>

int main(int argc, char *argv[]) {
  int count;

  printf("The command line has %d arguments:\n", argc - 1);
  for (count = 1; count < argc; ++count) {
    printf("%d: %s\n", count, argv[count]);
  }
  putchar('\n');

  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int i, times;

  if (argc < 2 || (times = atoi(argv[1])) < 1) {
    printf("Usage: %s positive-number\n", argv[0]);
  } else {
    for (i = 0; i < times; ++i) {
      puts("Hello, good looking!");
    }
  }
  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>
#define LIM 30                  // 大小
char *s_gets(char *st, int n);  // 函数原型

int main() {
  char number[LIM];  // 数组
  char *end;         // 结束位置
  long value;        // 对应数值

  puts("Enter a number (empty line to quit):");
  while (s_gets(number, LIM) && number[0] != '\0') {
    value = strtol(number, &end, 10);
    printf("base 10 input, base 10 output: %ld, stopped at %s (%d)\n", value,
           end, *end);  // 值，字符串结束地址，地址存的值
    value = strtol(number, &end, 16);
    printf("base 16 input, base 10 output: %0lx, stopped at %s (%d)\n", value,
           end, *end);
    puts("Next number:");
  }
  puts("Bye!\n");

  return 0;
}

char *s_gets(char *st, int n) {
  char *ret_val;
  int i = 0;

  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    while (st[i] != '\n' && st[i] != '\0') {
      ++i;
    }
    if (st[i] == '\n') {
      st[i] = '\0';
    } else {
      while (getchar() != '\n') {
        continue;
      }
    }
  }
  return ret_val;
} */
/* #include <stdio.h>
#include <string.h>
char *s_gets(char *st, int n) {
  char *ret_val;

  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    char *find = strchr(ret_val, '\n');
    if (*find == '\n') {
      *find = '\0';
    } else {
      while (getchar() != '\n') {
        continue;
      }
    }
  }
  return ret_val;
} */
/* #include <ctype.h>
#include <string.h>

const char *func(char *str) {
  while (!isspace(*str)) {
    if (!*str) {
      return NULL;
    }
    ++str;
  }
  return str;
} */
/* #include <stdio.h>

int main() {
  printf("Hello World!\n");

  return 0;
} */
/* #include <ctype.h>
#include <stdio.h>

void func(char *dest, int n) {
  char ch;
  while (n) {
    ch = getchar();
    if (isspace(ch)) {
      return;
    }
    *dest = ch;
    --n;
    ++dest;
  }
}

int main() {
  char arr[10];
  func(arr, 10);
  for (int i = 0; i < 10; ++i) {
    putchar(arr[i]);
  }
  putchar('\n');
  return 0;
} */
/* #include <stdio.h>
#include <string.h>
void func(char *arr, int n) {
  scanf("%s", arr);
  while (getchar() != '\n') {
    continue;
  }
  // 计算字符串大小，超过就截断
  if (strlen(arr) > n) {
    arr[n] = '\0';
  }
}
int main() {
  char arr[10];
  func(arr, 5);
  printf("%s", arr);
  return 0;
} */
/* #include <stdio.h>

char *func(char *str, char ch) {
  while (*str != ch && *str != '\0') {
    str++;
  }

  if (*str == '\0') {
    return NULL;
  }

  return str;
}

int main() {
  char ch = 0;
  char arr[12] = {0};

  scanf("%11s", arr);
  while (getchar() != '\n') {
    continue;
  }
  ch = getchar();
  char *p = func(arr, ch);
  if (p != NULL) {
    printf("%c %zd\n", *p, p - arr + 1);
  } else {
    printf("Character not found\n");
  }

  return 0;
}
 */
/* #include <stdbool.h>
#include <stdio.h>

bool is_within(const char *str, char ch) {
  while (*str != ch && *str) {
    ++str;
  }

  if (!*str) {
    return false;
  }

  return true;
}

int main() {
  char arr[50] = {0};
  char ch = 0;

  while (true) {
    scanf("%s", arr);

    while (getchar() != '\n') {
      continue;
    }

    ch = getchar();
    if (is_within(arr, ch)) {
      printf("true\n");
    } else {
      printf("false\n");
    }
  }

  return 0;
} */
/* #include <stdio.h>

char *myStrncpy(char *dest, const char *src, size_t n) {
  while (n--) {
    *(dest + n) = *(src + n);
  }
  return dest;
} */
/* #include <string.h>
char *string_in(char *str1, const char *str2) {

  int len = strlen(str2);
  while (*str1) {
    if (!strncmp(str1, str2, len)) {
      return str1;
    }
    ++str1;
  }
  return NULL;
} */
/* #include <stdio.h>
void inverse(char *str) {
  char *ptr = str;
  while (*ptr) {
    ++ptr;
  }
  --ptr;
  while (ptr > str) {
    char temp = *ptr;
    *ptr = *str;
    *str = temp;
    ++str;
    --ptr;
  }
}
int main() {
  char str[] = "Hello, World!";
  printf("Original string: %s\n", str);

  inverse(str);
  printf("Reversed string: %s\n", str);

  return 0;
} */
/* #include <ctype.h>
#include <stdio.h>
#include <string.h>

void deleteSpace(char *str) {
  char *write_ptr = str;
  char *read_ptr = str;

  while (*read_ptr) {
    if (!isspace(*read_ptr)) {
      *write_ptr = *read_ptr;
      ++write_ptr;
    }
    ++read_ptr;
  }
  *write_ptr = '\0';
} */
/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 10
#define MAX_LENGTH 100

void printSourceStrings(char strings[][MAX_LENGTH], int count) {
  printf("Source String List:\n");
  for (int i = 0; i < count; ++i) {
    printf("%s\n", strings[i]);
  }
  printf("\n");
}

int compareStrings(const void *a, const void *b) {
  return strcmp((const char *)a, (const char *)b);
}

void printSortedASCII(char strings[][MAX_LENGTH], int count) {
  qsort(strings, count, sizeof(strings[0]), compareStrings);

  printf("Sorted ASCII Order:\n");
  for (int i = 0; i < count; ++i) {
    printf("%s\n", strings[i]);
  }
  printf("\n");
}

int compareLength(const void *a, const void *b) {
  return strlen(*(const char **)a) - strlen(*(const char **)b);
}

void printSortedLength(char strings[][MAX_LENGTH], int count) {
  char *temp[MAX_STRINGS];
  for (int i = 0; i < count; ++i) {
    temp[i] = strings[i];
  }

  qsort(temp, count, sizeof(temp[0]), compareLength);

  printf("Sorted Length Order:\n");
  for (int i = 0; i < count; ++i) {
    printf("%s\n", temp[i]);
  }
  printf("\n");
}

void printSortedWordLength(char strings[][MAX_LENGTH], int count) {
  char *temp[MAX_STRINGS];
  for (int i = 0; i < count; ++i) {
    temp[i] = strings[i];
  }

  qsort(temp, count, sizeof(temp[0]), compareStrings);

  printf("Sorted Word Length Order:\n");
  for (int i = 0; i < count; ++i) {
    char *firstWord = strtok(temp[i], " ");
    printf("%s\n", firstWord);
  }
  printf("\n");
}

int main() {
  char strings[MAX_STRINGS][MAX_LENGTH];
  int count = 0;

  printf("Enter up to 10 strings (or press Ctrl+D to stop):\n");

  while (count < MAX_STRINGS &&
         fgets(strings[count], MAX_LENGTH, stdin) != NULL) {
    strings[count][strcspn(strings[count], "\n")] = '\0';  // 移除换行符
    count++;
  }

  int choice;
  do {
    printf("Menu:\n");
    printf("1. Print Source String List\n");
    printf("2. Print Strings in ASCII Order\n");
    printf("3. Print Strings in Length Order\n");
    printf("4. Print Strings in Word Length Order\n");
    printf("5. Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printSourceStrings(strings, count);
        break;
      case 2:
        printSortedASCII(strings, count);
        break;
      case 3:
        printSortedLength(strings, count);
        break;
      case 4:
        printSortedWordLength(strings, count);
        break;
      case 5:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid choice! Please try again.\n");
        break;
    }

    while (getchar() != '\n')
      ;  // 清空输入缓冲区

  } while (choice != 5);

  return 0;
} */
/* #include <ctype.h>
#include <stdio.h>

int main() {
  unsigned int num_punct = 0;
  unsigned int num_alpha = 0;
  unsigned int num_lower = 0;
  unsigned int num_upper = 0;
  unsigned int num_digit = 0;
  unsigned int num_word = 0;
  int in_word = 0;
  char ch = 0;

  while ((ch = getchar()) != EOF) {
    if (isspace(ch)) {
      in_word = 0;
    } else {
      if (!in_word) {
        ++num_word;
        in_word = 1;
      }

      if (isdigit(ch)) {
        ++num_digit;
      } else if (isalpha(ch)) {
        ++num_alpha;
        if (isupper(ch)) {
          ++num_upper;
        } else {
          ++num_lower;
        }
      } else if (ispunct(ch)) {
        ++num_punct;
      }
    }
  }

  printf("%u %u %u %u %u\n", num_word, num_upper, num_lower, num_punct,
         num_digit);

  return 0;
} */
/* #include <stdio.h>

int main() {
  printf("Hello World!\n");
  return 0;
} */
/* #include <ctype.h>
#include <limits.h>
#include <stdio.h>

int myAtoi(char *str) {
  int result = 0;
  int sign = 1;
  while (isspace(*str)) {
    ++str;
  }

  if (*str == '+' || *str == '-') {
    if (*str == '-') {
      sign = -1;
    }
    ++str;
  }

  while (isdigit(*str)) {
    int digit = *str - '0';

    if (result == INT_MAX || (result > INT_MAX / 10 && digit > INT_MAX % 10)) {
      return (sign == 1) ? INT_MAX : INT_MIN;
    }
    result = result * 10 + digit;
  }

  return result * sign;
} */
/* #include <stdio.h>

int main() {
  int *p = NULL;
  return 0;
}
 */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
static unsigned long next = 1;

unsigned int rand0() {
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}

void srand0(unsigned int seed) { next = seed; }

int main() {
  int count;
  unsigned seed;

  printf("Please enter your choice for seed.\n");
  while (scanf("%u", &seed) == 1) {
    srand0(seed);
    for (count = 0; count < 5; ++count) {
      printf("%d\n", rand0());
    }
    printf("Please enter next seed (q to quit):\n");
  }
  printf("Done.\n");

  return 0;
} */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/diceroll.h"

int main() {
  // 次数和点数
  int dice, roll;
  // 几个面
  int sides;
  // 几个状态
  int status;

  // 生成种子
  srand((unsigned int)time(NULL));
  // 打印提示语句
  printf("Enter the number of sides per die, 0 to stop.\n");
  // 如果输入的相符并且面数大于 1，循环继续
  while (scanf("%d", &sides) == 1 && sides > 0) {
    // 几次
    printf("How many dice?\n");
    // 如果状态不符
    if ((status = scanf("%d", &dice)) != 1) {
      // 如果文件末尾，退出
      if (status == EOF) {
        break;
      } else {
        // 否则提示语句，再循环一次
        printf("You should have entered an integer.");
        printf(" Let's begin again.\n");
        while (getchar() != '\n') {
          continue;
        }
        printf("How many sides? Enter 0 to stop.\n");
        continue;
      }
    }
    // 求点数
    roll = roll_n_dice(dice, sides);
    printf("You have rolled a %d using %d %d-sides dice.\n", roll, dice, sides);
    printf("How many sides? Enter 0 to stop.\n");
  }
  // 调用几次
  printf("The rollem() function was called %d times.\n", roll_count);

  // 再见！
  printf("GOOD FORTUNE TO YOU!\n");

  return 0;
} */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
  // 指针
  double* ptd;
  // 空间大小
  int max;
  // 数量
  int number;
  int i = 0;

  puts("What is the maxinum number of type double entries?");
  if (scanf("%d", &max) != 1) {
    puts("Number not correctly entered -- bye.");
    exit(EXIT_FAILURE);
  }
  ptd = (double*)malloc(max * sizeof(double));
  if (ptd == NULL) {
    puts("Memory allocation failed. Goodbye.");
    exit(EXIT_FAILURE);
  }

  puts("Enter the values (q to quit):");
  while (i < max && scanf("%lf", &ptd[i]) == 1) ++i;
  printf("Here are your %d entries:\n", number = i);
  for (i = 0; i < number; ++i) {
    printf("%7.2f ", ptd[i]);
    if (i % 7 == 6) putchar('\n');
  }
  if (i % 7 != 0) putchar('\n');
  puts("Done.");
  free(ptd);

  return EXIT_SUCCESS;
} */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

int main() {
  int n = 5;
  int m = 6;
  int ar2[n][m];
  int(*p2)[6];
  int(*p3)[m];
  p2 = (int(*)[6])malloc(n * 6 * sizeof(int));
  p3 = (int(*)[m])malloc(n * m * sizeof(int));
  ar2[1][2] = p2[1][2] = 12;
  return EXIT_SUCCESS;
} */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int static_store = 30;
const char * pcg = "String Literal";
int main() {
  int auto_store = 40;
  char auto_string [] = "Auto char Array";
  int *pi;
  char *pcl;

  pi = (int *) malloc(sizeof(int));
  *pi = 35;
  pcl = (char *) malloc(strlen("Dynamic String") + 1);
  strcpy(pcl, "Dynamic String");

} */
/* void ofmouth(int a1[const], int a2[restrict], int n);
double stick(double ar[static 20]); */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void critic(int *ptr);
int main() {
  int units;

  printf("How many pounds to a firkin of butter!\n");
  scanf("%d", &units);
  while (units != 56) {
    critic(&units);
  }
  printf("You must have looked it up!\n");

  return 0;
}
void critic(int *ptr) {
  printf("No luck, my friend. Try again.\n");
  scanf("%d", ptr);
} */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>

#include "../inc/pe12-2a.h"


int main() {
  int mode;
  double distance;
  double fuel;

  printf("Enter 0 for metric mode, 1 for US mode: ");
  while (true) {
    set_mode(&mode);
    if (mode == -1) break;
    get_info(mode, &distance, &fuel);
    show_info(mode, distance, fuel);
    printf("Enter 0 for metric mode, 1 for US mode");
    printf(" (-1 to quit): ");
  }
  printf("Done.\n");
  return 0;
} */
/* #include <stdio.h>

void func() {
  static int count = 0;
  ++count;
  printf("%d ", count);
}

int main() {
  for (int i = 0; i < 10; ++i) {
    func();
  }
  putchar('\n');
  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] < arr[j + 1]) swap(&arr[j], &arr[j + 1]);
    }
  }
}

int main() {
  srand((unsigned int)time(NULL));
  int arr[100];
  for (int i = 0; i < 100; ++i) {
    arr[i] = rand() % 10 + 1;
  }
  bubbleSort(arr, sizeof(arr) / sizeof(int));
  for (int i = 0; i < 100; ++i) {
    printf("%2d ", arr[i]);
    if (i % 10 == 9) putchar('\n');
  }
  putchar('\n');
  return 0;
}
 */
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "../inc/diceroll.h"

int main() {
  int sets;
  int dice;
  int sides;

  printf("Enter the number of sets; enter q to stop: ");

  while (scanf("%d", &sets) == 1) {
    printf("How many sides and how many dice? ");
    scanf("%d %d", &dice, &sides);
    printf("Here are %d sets of %d %d-sides throws.\n", sets, dice, sides);
    for (int i = 1; i <= sets; ++i) {
      printf("%  d", roll_n_dice(dice, sides));
      if (i % 15 == 0) putchar('\n');
    }
    putchar('\n');
    printf("How many sets? Enter q to stop: ");
  }
  return 0;
} */
/* #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
  srand((unsigned int)time(NULL));
  while (1) {
    for (int i = 0; i < 10; ++i) {
      printf(" %2d", rand() % 100 + 1);
    }
    printf("\n");
    system("pause");
  }
  return 0;
} */
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>

int main() {
  printf("Hello World!");
  int arr[10] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 10; ++i) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}