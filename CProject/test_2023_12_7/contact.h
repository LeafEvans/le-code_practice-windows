#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define DEFAULT_SZ 3
#define INC_SZ 2
#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TEL 12
#define MAX_ADDR 30

typedef struct PeoInfo {
  char name[MAX_NAME];
  int age;
  char sex[MAX_SEX];
  char tel[MAX_TEL];
  char addr[MAX_ADDR];
} PeoInfo;  // 人的信息

// 静态版本
// typedef struct Contact {
//  PeoInfo data[MAX];  // 存放人的信息
//  int count;  // 记录当前通讯录中实际人的个数
//} Contact;  // 通讯录

typedef struct Contact {
  PeoInfo *data;  // 存放人的信息
  int count;      // 记录当前通讯录中实际人的个数
  int capacity;   // 当前通讯录的容量
} Contact;

int initContact(Contact *pc);
void addContact(Contact *pc);
void showContact(Contact *pc);
void delContact(Contact *pc);
void searchContact(Contact *pc);
void modifyContact(Contact *pc);
void sortContact(Contact *pc);
void checkCapacity(Contact *pc);
void destroyContact(Contact *pc);