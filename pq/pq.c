#include <stdlib.h>
#include "pq.h"

struct pqueue { Item *A; int heapsize; };

int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

void Swap(PQ pq, int a, int b){
	Item tmp;
	tmp = pq->A[a];
	pq->A[a] = pq->A[b];
	pq->A[b] = tmp;
	return;
}

void HEAPify(PQ pq, int i){
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	if( (l<pq->heapsize) && (ITEMgreat(pq->A[l],pq->A[i])) )
		largest = l;
	else
		largest = i;
	if( (r<pq->heapsize) && (ITEMgreat(pq->A[r],pq->A[largest])) )
		largest = r;
	if(largest != i){
		Swap(pq, i, largest);
		HEAPify(pq, largest);
	}
	return;
}

PQ PQinit(int maxN){
	PQ pq = malloc(sizeof(*pq));
	pq->A = malloc(maxN*sizeof(Item));
	pq->heapsize = 0;
	return pq;
}

int PQempty(PQ pq){
	return pq->heapsize == 0;
}

int PQsize(PQ pq){
	return pq->heapsize;
}

Item PQshowMax(PQ pq){
	return pq->A[0];
}

void PQdisplay(PQ pq){
	int i;
	for(i=0;i<pq->heapsize;i++)
		ITEMprint(pq->A[i]);
}

void PQinsert(PQ pq, Item item){
	int i;
	i = pq->heapsize++;
	while( (i>=1) && (ITEMless(pq->A[PARENT(i)], item)) ){
		pq->A[i] = pq->A[PARENT(i)];
		i = PARENT(i);
	}
	pq->A[i] = item;
	return;
}

Item PQextractMax(PQ pq){
	Item item = pq->A[0];
	Swap(pq, 0, pq->heapsize-1);
	h->heapsize--;
	HEAPify(pq, 0);
	return item;
}

void PQchange(PQ pq, int pos, Item item){
	while( (pos>=1) && (ITEMless(pq->A[PARENT(pos)], item)) ){
		pq->A[pos] = pq->A[PARENT(pos)];
		pos = PARENT(pos);
	}
	pq->A[pos] = item;
	HEAPify(pq, pos);
	return;
}
	