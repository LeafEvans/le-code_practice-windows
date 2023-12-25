#include "contact.h"

// 静态版本
// void initContact(Contact *pc) {
//   assert(pc);

//   pc->count = 0;

//  memset(pc->data, 0, sizeof(pc->data));
//}

int initContact(Contact *pc) {
  assert(pc);
  pc->count = 0;
  pc->data = (PeoInfo *)calloc(DEFAULT_SZ, sizeof(PeoInfo));
  if (pc->data == NULL) {
	printf("initContact::%s\n", strerror(errno));
	return 1;
  }
  pc->capacity = DEFAULT_SZ;
  loadContact(pc);
  return 0;
}

void loadContact(Contact *pc) {
  FILE *pfRead = fopen("contact.txt", "rb");

  if (pfRead == NULL) {
	perror("loadContact");
	return;
  }

  PeoInfo temp = {0};

  while (fread(&temp, sizeof(PeoInfo), 1, pfRead)) {
	checkCapacity(pc);
	pc->data[pc->count] = temp;
	pc->count++;
  }
  fclose(pfRead);
  pfRead = NULL;
}
// 静态版本
// void addContact(Contact *pc) {
//  assert(pc);

//  if (pc->count == MAX) {
//	printf("通讯录已满，无法添加\n");
//	return;
//  }

//  printf("请输入名字:>\n");
//  scanf("%s", pc->data[pc->count].name);

//  printf("请输入年龄:>\n");
//  scanf("%d", &(pc->data[pc->count].age));

//  printf("请输入性别:>\n");
//  scanf("%s", pc->data[pc->count].sex);

//  printf("请输入电话:>\n");
//  scanf("%s", pc->data[pc->count].tel);

//  printf("请输入地址:>\n");
//  scanf("%s", pc->data[pc->count].addr);

//  pc->count++;
//  printf("增加成功\n");
//}

void checkCapacity(Contact *pc) {
  if (pc->count == pc->capacity) {
	PeoInfo *ptr =
		(PeoInfo *)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
	if (ptr == NULL) {
	  printf("addContact::%s\n", strerror(errno));
	  return;
	} else {
	  pc->data = ptr;
	  ptr = NULL;
	  pc->capacity += INC_SZ;
	  printf("增容成功\n");
	}
  }
}

void addContact(Contact *pc) {
  assert(pc);

  checkCapacity(pc);

  printf("请输入名字:>\n");
  scanf("%s", pc->data[pc->count].name);

  printf("请输入年龄:>\n");
  scanf("%d", &(pc->data[pc->count].age));

  printf("请输入性别:>\n");
  scanf("%s", pc->data[pc->count].sex);

  printf("请输入电话:>\n");
  scanf("%s", pc->data[pc->count].tel);

  printf("请输入地址:>\n");
  scanf("%s", pc->data[pc->count].addr);

  pc->count++;
  printf("增加成功\n");
}

void showContact(Contact *pc) {
  assert(pc);

  printf("%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话",
		 "地址");

  for (int i = 0; i < pc->count; ++i) {
	printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", pc->data[i].name,
		   pc->data[i].age, pc->data[i].sex, pc->data[i].tel, pc->data[i].addr);
  }
}

static int findByName(const Contact *pc, const char *name) {
  assert(pc);

  for (int i = 0; i < pc->count; ++i) {
	if (strcmp(pc->data[i].name, name) == 0) {
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
	pc->data[i] = pc->data[i + 1];
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

  printf("%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话",
		 "地址");
  printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", pc->data[pos].name,
		 pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tel,
		 pc->data[pos].addr);
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
  scanf("%s", pc->data[pos].name);

  printf("请输入年龄:>\n");
  scanf("%d", &(pc->data[pos].age));

  printf("请输入性别:>\n");
  scanf("%s", pc->data[pos].sex);

  printf("请输入电话:>\n");
  scanf("%s", pc->data[pos].tel);

  printf("请输入地址:>\n");
  scanf("%s", pc->data[pos].addr);

  printf("修改成功\n");
}

static int cmpPeoByName(const void *e1, const void *e2) {
  return strcmp(((PeoInfo *)e1)->name, ((PeoInfo *)e2)->name);
}

void sortContact(Contact *pc) {
  assert(pc);

  qsort(pc->data, pc->count, sizeof(PeoInfo), cmpPeoByName);
}

void destroyContact(Contact *pc) {
  assert(pc);
  free(pc->data);
  pc->data = NULL;
}

void saveContact(const Contact *pc) {
  assert(pc);
  FILE *pfWrite = fopen("contact.txt", "wb");
  if (pfWrite == NULL) {
	perror("saveContact");
	return;
  }

  for (int i = 0; i < pc->count; ++i) {
	fwrite(pc->data + i, sizeof(PeoInfo), 1, pfWrite);
  }

  fclose(pfWrite);
  pfWrite = NULL;
}