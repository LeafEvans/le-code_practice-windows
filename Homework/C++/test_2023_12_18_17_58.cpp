#include <cstring>
#include <iostream>
using namespace std;

int main(void) {
  char stu_name[5][20] = {0};

  for (int i = 0; i < 5; ++i) {
    cin >> stu_name[i];
  }

  char tmp[20] = {0};

  strcpy(tmp, stu_name[0]);
  strcpy(stu_name[0], stu_name[4]);
  strcpy(stu_name[4], tmp);

  for (int i = 0; i < 5; ++i) {
    cout << stu_name[i] << endl;
  }

  return 0;
}
