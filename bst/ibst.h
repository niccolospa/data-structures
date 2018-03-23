#ifndef LB_IBST_H
#define LB_IBST_H

#include "Interval.h"

typedef struct intervalbinarysearchtree *IBST;

void IBSTinit(IBST);
void IBSTinsert(IBST,Interval);
void IBSTdelete(IBST,Interval);
Interval IBSTsearch(IBST,Interval);
int IBSTcount(IBST);
int IBSTempty(IBST);

#endif