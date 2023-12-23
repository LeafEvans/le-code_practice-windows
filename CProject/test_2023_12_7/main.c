#include "contact.h"

enum Option {
  EXIT, ADD, DEL, SEARCH, MODIFY, SHOW, SORT
};

void menu(void) {
  printf("********************************************\n");
  printf("*****      1.add            2.del      *****\n");
  printf("*****      3.search         4.modify   *****\n");
  printf("*****      5.show           6.sort     *****\n");
  printf("*****      0.exit                      *****\n");
  printf("********************************************\n");
}

int main(void) {
  int input = 0;
  Contact con;

  initContact(&con);

  do {
	menu();

	printf("请选择:>\n");
	scanf("%d", &input);

	switch (input) {
	  case ADD: addContact(&con);
		break;
	  case DEL: delContact(&con);
		break;
	  case SEARCH: searchContact(&con);
		break;
	  case MODIFY: modifyContact(&con);
		break;
	  case SHOW: showContact(&con);
		break;
	  case SORT: sortContact(&con);
		break;
	  case EXIT:
		destroyContact(&con);
		break;
	  default: printf("选择错误\n");
		break;
	}
  } while (input);

  return 0;
}