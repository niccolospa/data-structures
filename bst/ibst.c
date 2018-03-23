#include <stdlib.h>
#include <stdio.h>
#include "ibst.h"

typedef struct IBSTnode *link;
struct IBSTnode {Interval interval; link l, r; int N; int max;};
struct intervalbinarysearchtree {link head; int N; link z;};

link NEW(Interval interval, link l, link r, int N, int max){
	link x = malloc(sizeof(*x));
	x->interval = interval;
	x->l = l;
	x->r = r;
	x->N = N;
	x->max = max;
	return x;
}

IBST IBSTinit(){
	IBST ibst = malloc(sizeof(*ibst));
	ibst->N = 0;
	ibst->head = (ibst->z = NEW(INTERVALsetvoid(),NULL,NULL,0,-1));
	return ibst;
}

int max(int a, int b, int c){
	int m = a;
	if (b > m) m = b;
	if (c > m) m = c;
	return m;
}

int IBSTcount(IBST ibst){
	return ibst->N;
}

int IBSTempty(IBST ibst){
	if(IBSTcount(ibst) == 0)
		return 1;
	return 0;
}

link insertR(link h, Interval interval, link z){
	if(h == z)
		return NEW(interval, z, z, 1, INTERVAlhigh(interval));
	if(INTERVALless(interval, h->interval)){
		h->l = insertR(h->l, interval, z);
		h->max = max(h->max, h->l->max, h->r->max);
	}
	else {
		h->r = insertR(h->r, interval, z);
		h->max = max(h->max, h->l->max, h->r->max);
	}
	(h->N)++;
	return h;
}

void IBSTinsert(IBST ibst, Interval interval){
	ibst->head = insertR(ibst->head, interval, ibst->z);
	ibst->N++;
}

link rotL(link h){
	link x = h->r;
	h->r = x->l;
	x->l = h;
	x->N = h->N;
	h->N = h->l->N + h->r->N + 1;
	h->max = max(INTERVALhigh(h->interval), h->l->max, h->r->max);
	x->max = max(INTERVALhigh(x->interval), x->l->max, x->r->max);
	return x;
}

link rotR(link h){
	link x = h->l;
	h->l = x->r;
	x->r = h;
	x->N = h->N;
	h->N = h->r->N + h->l->N +1;
	h->max = max(INTERVALhigh(h->interval), h->l->max, h->r->max);
	x->max = max(INTERVALhigh(x->interval), x->l->max, h->r->max);
	return x;
}

link partR(link h, int k){
	int t = h->l->N;
	if(t > k){
		h->l = partR(h->l, k);
		h = rotR(h);
	}
	if(t < k){
		h->r = partR(h->r, k-t-1);
		h = rotL(h);
	}
	return h;
}

link joinLR(link a, link b, link z){
	if(b == z)
		return a;
	b = partR(b, 0);
	b->l = a;
	b->N = a->N + b->r->N +1;
	b->max = max(INTERVALhigh(b->interval), a->max, b->r->max);
	return b;
}

link deleteR(link h, Interval interval, link z){
	link x;
	if(h == z)
		return z;
	if(INTERVALless(interval, h->interval)){
		h->l = deleteR(h->l, interval, z);
		h->max = max(INTERVALhigh(h->item), h->l->max, h->r->max);
	}
	if(INTERVALless(h->interval, interval)){
		h->r = deleteR(h->r, interval, z);
		h->max = max(INTERVALhigh(h->item), h->l->max, h->r->max);
	}
	(h->N)--;
	if(INTERVALeq(interval, h->interval)){
		x = h;
		h = joinLR(h->l, h->r, z);
		free(x);
	}
	return h;
}

void IBSTdelete(IBST ibst, Interval interval){
	ibst->head = deleteR(ibst->head, interval, ibst->z);
	ibst->N--;
}

Interval searchR(link h, Interval interval, link z){
	if(h == z)
		return INTERVALsetvoid();
	if(INTERVALoverlap(interval, h->interval))
		return h->interval;
	if(INTERVALless_int(interval, h->l->max))
		return searchR(h->l, interval, z);
	else
		return searchR(h->r, interval, z);
}

Interval IBSTsearch(IBST ibst, Interval interval){
	return searchR(ibst->head, interval, ibst->z);
}