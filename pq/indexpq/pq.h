#ifndef LB_PQ_H
#define LB_PQ_H

typedef struct pqueue *PQ;

PQ PQinit(int);
int PQempty(PQ);
int PQsize(PQ);
void PQinsert(PQ,Item);
Item PQshowMax(PQ);
Item PQextractMax(PQ);
void PQdisplay(PQ,int);
void PQchange(PQ,Item);

#endif