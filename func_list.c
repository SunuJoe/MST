// func_list.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void listInit(List* plist)
{
  plist->head = (Node*)malloc(sizeof(Node));
  plist->head->next = NULL;
  plist->cur = NULL;
  plist->bef = NULL;
  plist->num = 0;
  plist->comp = NULL;
}

void setRule(List* plist, func_list action)
{
  plist->comp = action;
}

// func for insert.
void headInsert(List* plist, Ldata val)
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = val;
  newNode->next = plist->head->next;
  plist->head->next = newNode;
  (plist->num)++;
}

void ruleInsert(List* plist, Ldata val)
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = val;

  Node* pred = plist->head;
  while(pred->next != NULL && plist->comp(val, pred->next->data) != 0)
  {
    pred = pred->next;
  }
  newNode->next = pred->next;
  pred->next = newNode;
  (plist->num)++;
}

void listInsert(List* plist, Ldata val)
{
  if(plist->comp == NULL)
    headInsert(plist, val);
  else
    ruleInsert(plist, val);
}

int firstSearch(List* plist, Ldata* rval)
{
  if(plist->head->next == NULL)
  {
    printf("there's no Node\n");
    return FALSE;
  }
  else
  {
    plist->bef = plist->head;
    plist->cur = plist->head->next;
    *rval = plist->cur->data;
    return TRUE;
  }
}

int nextSearch(List* plist, Ldata* rval)
{
  if(plist->cur->next == NULL)
    return FALSE;
  else
  {
    plist->bef = plist->cur;
    plist->cur = plist->cur->next;
    *rval = plist->cur->data;
    return TRUE;
  }
}

Ldata listDelete(List* plist)
{
  if(plist->head->next == NULL)
  {
    printf("Delete error : no data\n");
    exit(-1);
  }
  else
  {
    Node* temp = plist->cur;
    Ldata temp_data = plist->cur->data;
    plist->bef->next = plist->cur->next;
    plist->cur = plist->bef;
    free(temp);
    (plist->num)--;
    return temp_data;
  }
}

int getNum(List* plist)
{
  return plist->num;
}
