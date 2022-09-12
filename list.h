// list.h

#ifndef __LIST_H__
#define __LIST_H__

#define TRUE 1
#define FALSE 0

typedef int Ldata;
typedef struct __node
{
  Ldata data;
  struct __node* next;
} Node;

typedef int (*func_list)(Ldata val1, Ldata val2);
typedef struct __list
{
  Node* head;
  Node* cur;
  Node* bef;
  int num;
  func_list comp;
} List;

void listInit(List* plist);
void setRule(List* plist, func_list action);
void listInsert(List* plist, Ldata val);
int firstSearch(List* plist, Ldata* rval);
int nextSearch(List* plist, Ldata* rval);
Ldata listDelete(List* plist);
int getNum(List* plist);

#endif
