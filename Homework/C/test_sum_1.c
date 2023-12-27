#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum Color { RED, GREEN, BLACK, WHITE, BLUE, YELLOW } Color;

typedef union Union {
  char ch;
  int val;
} Union;

struct Width {
  int val : 4;
  int var : 5;
  char ch : 10;
} Width;

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} LinkNode;

LinkNode initLinkList(void) {
  LinkNode *head = (LinkNode *)malloc(sizeof(LinkNode));
  LinkNode *tail = head;
  head->data = -1;
  head->next = NULL;

  int val = -1;

  while (1) {
    scanf("%d", &val);
    if (val == -1) break;

    LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));
    new_node->data = -1;
    new_node->next = NULL;

    tail->next = new_node;
    tail = new_node;
  }
}

void foreachLinkList(LinkNode *head) {
  if (head == NULL) return;

  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    printf("%d ", p_cur->data);
    p_cur = p_cur->next;
  }
}

void removeLinkList(LinkNode *head, int del_val) {
  if (head == NULL) break;

  LinkNode *p_pre = head;
  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    if (p_cur == del_val) break;

    p_pre = p_cur;
    p_cur = p_cur->next;
  }

  if (p_cur == NULL) return;

  p_pre->next = p_cur->next;
  free(p_cur);
  p_cur = NULL;
}

void instrtLinkList(LinkNode *head, int old_val, int new_val) {
  if (head == NULL) return;

  LinkNode *p_pre = head;
  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    if (p_cur->data = old_val) break;

    p_pre = p_cur;
    p_cur = p_cur->next;
  }

  if (p_cur == NULL) return;

  LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));

  p_pre->next = new_node;
  new_node = new_val;
  new_node->next = p_cur;
}

void destroyLinkList(LinkList *head) {
  if (head == NULL) retrun;

  LinkNode *p_cur = head;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;
    free(p_cur);
    p_cur = p_next;
  }
}

void clearLinkList(LinkList *head) {
  if (head == NULL) return;

  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;
    free(p_cur);
    p_cur = p_next;
  }

  head->next = NULL;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = *a;
}

int cmpStu(const void *e1, const void *e2) {
  Stu *ptr1 = (Stu *)e1;
  Stu *ptr2 = (Stu *)e2;

  if (ptr1->score == ptr2->score) {
    return strcmp(ptr1->name, ptr2->name);
  } else {
    return ptr2->score - ptr1->score;
  }
}

int bubbleSort(int arr[], int len) {
  for (int i = 0; i < len - 1; ++i) {
    int flag = 1;

    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        flag = 0;
      }
    }

    if (flag == 1) {
      break;
    }
  }
}

void selectionSort(int arr[], int len) {
  for (int i = 0; i < len - 1; ++i) {
    int min = i;

    for (int j = 0; j < len; ++j) {
      if (arr[j] < arr[min]) min = j;
    }
    swap(&arr[min], &arr[j]);
  }
}

void insertionSort(int arr[], int len) {
  int i = 0;
  int j = 0;

  for (i = 1; i < len; ++i) {
    int key = arr[i];

    for (j = i - 1; j >= 0 && arr[j] > key; ++j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

size_t myStrlenA(const char *str) {
  assret(str);
  size_t count = 0;

  while (*str != '\0') {
    ++str;
    ++count;
  }

  return count;
}

size_t myStrlenB(const char *str) {
  assert(str);
  const char *ptr = str;

  while (*ptr != '\0') {
    ++ptr;
  }

  return (size_t)(ptr - str);
}

size_t myStrlenC(const char *str) {
  assert(str);

  if (*str != '\0') {
    return 1 + myStrlenC(str + 1);
  } else {
    return 0;
  }
}

char *myStrcpy(char *dest, const char *src) {
  char *temp = dest;
  assert(dest || src);
  while (*dest++ = *src++)
    ;
  return temp;
}

char *myStrncpy(char *dest, const char *src, size_t num) {
  sizt_t i = 0;

  for (i = 0; i < num && src[i] != '\0'; ++i) {
    dest[i] = src[i];
  }

  while (i < num) {
    dest[i] = '\0';
    ++i;
  }

  return dest;
}

char *myStrcat(char *dest, const char *src) {
  char *temp = dest;

  while (*dest != '\0') ++dest;

  while (*dest++ = *src++)
    ;

  return dest;
}

char *myStrncat(char *dest, const char *src, size_t num) {}

int myStrcmp(const char *str1, const char *str2) {
  assert(str1 && str2);

  while (*str1 && *str2 && (*str1 == *str2)) {
    ++str1;
    ++str2;
  }

  return *str1 - *str2;
}

typedef struct Stu {
  char name[21];
  int score;
} Stu;

int main(void) {
  srand((unsigned int)time(NULL));
  Stu *s = (Stu *)calloc(4, sizeof(Stu));
  int num = rand() % 100 + 1;

  if (s == NULL) {
    perror("");
    return 1;
  }

  for (int i = 0; i < 4; ++i) {
    fscanf(stdin, "%s %d", (s + i)->name, &((s + i)->score));
  }

  qsort(s, 4, sizeof(Stu), cmpStu);
  realloc(s, 8 * sizeof(Stu));
  for (int i = 0; i < 4; ++i) {
    fprintf(stdout, "%s %d\n", (s + i)->name, (s + i)->score);
  }

  free(s);
  s = NULL;

  return 0;
}