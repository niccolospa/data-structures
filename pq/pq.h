#ifndef LB_PQ_H
#define LB_PQ_H

#include "Item.h"

typedef struct pqueue *PQ;

PQ PQUEUEinit(int);
int PQUEUEempty(PQ);
void PQUEUEinsert(PQ, Item);
Item PQUEUEextractMax(PQ);
Item PQUEUEshowMax(PQ);
void PQUEUEdisplay(PQ);
int PQUEUEsize(PQ);
void PQUEUEchange(PQ pq, int pos, Item item);

#endif