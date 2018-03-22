#ifndef LB_LIST_H
#define LB_LIST_H

#include "../array/Item.h"


typedef struct singlylinkedlist *slink;
typedef slink *LSList;
typedef struct doublelinkedlist *dlink;
typedef dlink *LDList;

//Singly Linked List
int LSLISTcount(LSList);
void LSLISTtraverse(LSList);
void LSLISTinserthead(LSList,Item);
void LSLISTinserttail(LSList,Item);
int LSLISTsearch(LSList,Item);
void LSLISTdelete(LSList,Item);

//Double Linked List
int LDLISTcount(LDList);
void LDLISTtraverse(LDList);
void LDLISTinserthead(LDList,Item);
void LDLISTinserttail(LDList,Item);
int LDLISTsearch(LDList,Item);
void LDLISTdelete(LDList,Item);

#endif