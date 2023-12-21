#include "contact.h"

void initContact(Contact *pc) {
  assert(pc);

  pc->count = 0;

  memset(pc->date, 0, sizeof(pc->date));
}

void addContact(Contact *pc) {
  assert(pc);

  if (pc->count == MAX) {
	printf("通讯录已满，无法添加\n");
	return;
  }

  printf("请输入名字:>\n");
  scanf("%s", pc->date[pc->count].name);

  printf("请输入年龄:>\n");
  scanf("%d", &(pc->date[pc->count].age));

  printf("请输入性别:>\n");
  scanf("%s", pc->date[pc->count].sex);

  printf("请输入电话:>\n");
  scanf("%s", pc->date[pc->count].tel);

  printf("请输入地址:>\n");
  scanf("%s", pc->date[pc->count].addr);

  pc->count++;
  printf("增加成功\n");
}

void showContact(Contact *pc) {
  assert(pc);

  printf("%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");

  for (int i = 0; i < pc->count; ++i) {
	printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", pc->date[i].name,
		   pc->date[i].age, pc->date[i].sex,
		   pc->date[i].tel, pc->date[i].addr);
  }

}

static int findByName(const Contact *pc, const char *name) {
  assert(pc);

  for (int i = 0; i < pc->count; ++i) {
	if (strcmp(pc->date[i].name, name) == 0) {
	  return i;
	}
  }

  return -1;
}

void delContact(Contact *pc) {
  assert(pc);

  if (pc->count == 0) {
	printf("通讯录为空，没有信息可以删除\n");
  }

  char name[MAX_NAME] = {0};

  printf("请输入要删除的人的名字:>\n");
  scanf("%s", name);

  int pos = findByName(pc, name);

  if (pos == -1) {
	printf("要删除的人不存在\n");
	return;
  }

  for (int i = pos; i < pc->count - 1; ++i) {
	pc->date[i] = pc->date[i + 1];
  }
  pc->count--;  // 虽然上述代码无法删除最后一个元素的数据，但是因为数量进行减1操作，所以也访问不到
  printf("删除成功\n");
}

void searchContact(Contact *pc) {
  assert(pc);

  char name[MAX_NAME] = {0};

  printf("请输入要寻找的人的名字:>\n");
  scanf("%s", name);

  int pos = findByName(pc, name);

  if (pos == -1) {
	printf("要寻找的人不存在\n");
	return;
  }

  printf("%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");
  printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", pc->date[pos].name,
		 pc->date[pos].age, pc->date[pos].sex,
		 pc->date[pos].tel, pc->date[pos].addr);
}

void modifyContact(Contact *pc) {
  assert(pc);

  char name[MAX_NAME] = {0};

  printf("请输入要修改的人的名字:>\n");
  scanf("%s", name);

  int pos = findByName(pc, name);

  if (pos == -1) {
	printf("要修改的人不存在\n");
	return;
  }

  printf("要修改的人的信息已找到\n");

  printf("请输入名字:>\n");
  scanf("%s", pc->date[pos].name);

  printf("请输入年龄:>\n");
  scanf("%d", &(pc->date[pos].age));

  printf("请输入性别:>\n");
  scanf("%s", pc->date[pos].sex);

  printf("请输入电话:>\n");
  scanf("%s", pc->date[pos].tel);

  printf("请输入地址:>\n");
  scanf("%s", pc->date[pos].addr);

  printf("修改成功\n");
}

static int cmpPeoByName(const void *e1, const void *e2) {
  return strcmp(((PeoInfo *)e1)->name, ((PeoInfo *)e2)->name);
}

void sortContact(Contact *pc) {
  assert(pc);

  qsort(pc->date, pc->count, sizeof(PeoInfo), cmpPeoByName);
}