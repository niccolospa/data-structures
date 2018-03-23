#ifndef LB_ST_H
#define LB_ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int);
int STcount(ST);
int STempty(ST);
void STdisplay(ST);
void STinsert(ST,Item);
Item STsearch(ST,char*);

#endif