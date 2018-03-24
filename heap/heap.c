#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

struct heap { Item *A; int heapsize; };

int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

void Swap(Heap h, int a, int b){
	Item tmp;
	tmp = h->A[a];
	h->A[a] = h->A[b];
	h->A[b] = tmp;
	return;
}

Heap HEAPinit(int maxN){
	Heap h;
	h = malloc(sizeof(*h));
	h->A = malloc(maxN*sizeof(Item));
	h->heapsize = 0;
	return h;
}

void HEAPfill(Heap h, Item, item){
	int i;
	i = h->heapsize++;
	h->A[i] = item;
	return;
}

void HEAPdisplay(Heap h, Item item){
	int i;
	i = h->heapsize++;
	h->A[i] = item;
	return;
}

void HEAPdisplay(Heap h){
	int i;
	for(i=0; i<h->heapsize; i++)
		ITEMshow(h->A[i]);
}

void HEAPify(Heap h, int i){
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	if( (l < h->heapsize) && (ITEMgreat(h->A[l], h->A[i])) )
		largest = l;
	else
		largest = i;
	if( (r < h->heapsize) && (ITEMgreat(h->A[r], h->A[largest])) )
		largest = r;
	if(largest != i){
		Swap(h, i, largest);
		HEAPify(h, largest);
	}
	return;
}

void HEAPbuild(Heap h){
	int i;
	for(i=(h->heapsize)/2-1;i>=0;i--)
		HEAPify(h, i);
	return;
}

void HEAPsort(Heap h){
	int i, j;
	HEAPbuild(h);
	j = h->heapsize;
	for(i=h->heapsize-1;i>0;i--){
		Swap(h,0,i);
		h->heapsize--;
		HEAPify(h,0);
	}
	h->heapsize = j;
	return;
}
