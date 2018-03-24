#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "st.h"
#include "pq.h"

struct pqueue { int *A; ST tab; int *qp; int heapsize; };

int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

void Swap(PQ pa, int n1, int n2){
	int tmp;
	tmp = pq->A[n1];
	pq->A[n1] = pq->A[n2];
	pq->A[n2] = tmp;
	
	n1 = pq->A[n1];
	n2 = pq->A[n2];
	
	tmp = pq->qp[n1];
	pq->qp[n1] = pq->qp[n2];
	pq->qp[n2] = tmp;
	
	return;
}

void HEAPify(PQ pq, int i){
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	if( (l<pq->heapsize) && (CMPprio(STgetitem(pq->tab,pq->A[l]),STgetitem(pq->tab,pq->A[i]))==1) )
		largest = l;
	else
		largest = i;
	if( (r<pq->heapsize) && (CMPprio(STgetitem(pq->tab,pq->A[r]),STgetitem(pq->tab,pq->A[largest]))==1) )
		largest = r;
	if(largest != i){
		Swap(pq, i, largest);
		HEAPify(pq, largest);
	}
	return;
}

PQ PQinit(int maxN){
	PQ pq = malloc(sizeof(*pq));
	int i, size = STsize(maxN);
	if(size == -1)
		return NULL;
	pq->A = malloc(maxN * sizeof(int));
	pq->tab = STinit(size);
	pq->qp = malloc(size * sizeof(int));
	for(i=0;i<size;i++)
		pq->qp[i] = -1;
	pq->heapsize = 0;
	return pq;
}

int PQempty(PQ pq){
	return pq->heapsize == 0;
}

int PQsize(PQ pq){
	return pq->heapsize;
}

void PQinsert(PQ pq, Item item){
	int i, k;
	k = STinsert(pq->tab, item);
	i = pq->heapsize++;
	pq->qp[k] = i;
	while( (i>=1) && (CMPprio(STgetitem(pq->tab, pq->A[PARENT(i)]), item)==-1) ){
		pq->A[i] = pq->A[PARENT(i)];
		pq->qp[pq->A[i]] = i;
		i = (i-1)/2;
	}
	pq->A[i] = k;
	pq->qp[k] = i;
	return;
}

Item PQextractMax(PQ pq){
	Item item;
	Swap(pq, 0, pq->heapsize-1);
	item = STgetitem(pq->tab, pq->A[pq->heapsize-1]);
	pq->heapsize--;
	HEAPify(pq, 0);
	return item;
}

void PQchange(PQ pq, Item item){
	int pos = pq->qp[STgetindex(pq->tab, item)];
	int tmp = pq->A[pos];
	while( (pos >= 1) && (CMPprio(STgetitem(pq->tab,pq->A[PARENT(pos)]),item)==-1) ){
		pq->A[pos] = pq->A[PARENT(pos)];
		pq->qp[pq->A[pos]] = pos;
		pos = (pos-1)/2;
	}
	pq->A[pos] = tmp;
	pq->qp[tmp] = pos;
	
	STchange(pq->tab, item);
	HEAPify(pq, pos);
	return;
}

Item PQshowMax(PQ);

void PQdisplay(PQ,int);
