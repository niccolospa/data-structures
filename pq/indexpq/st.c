#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "st.h"

struct symboltable { Item *a; int N; int M; };

int STsize(int){
	int primes[50]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,
					47,53,59,61,67,71,73,79,83,89,97,101,
					103,107,109,113,127,131,137,139,149,151,
					157,163,167,173,179,181,191,193,197,199,
					211,223,227,229};
	int i, maxNallowed = primes[49]/2;
	if(maxN < maxNallowed){
		for(i=0;i<50;i++)
			if(2*maxN <= primes[i])
				return primes[i];
	}
	else
		printf("Too many entries!\n");
	return -1;
}

ST STinit(int maxN){
	int i;
	ST st = malloc(sizeof(*st));
	st->N = 0;
	st->M = maxN;
	st->a = malloc(st->M * sizeof(Item));
	for(i=0;i<st->M;i++)
		st->a[i] = ITEMsetvoid();
	return st;
}

int hash(KEYname k, int M){
	int h = 0, base = 127;
	for(;*k != '\0';k++)
		h = (base * h + *k) % M;
	return h;
}

int STcount(ST st){
	return st->N;
}

int STempty(ST st){
	if(STcount(st) == 0)
		return 1;
	return 0;
}

int full(ST st, int i){
	if(ITEMcheckvoid(st->a[i]))
		return 0;
	return 1;
}

int STinsert(ST st, Item item){
	int i = hash(GETname(item), st->M);
	while(full(st,i))
		i = (i+1) % st->M;
	st->a[i] = item;
	st->N++;
	return i;
}

Item STgetitem(ST st, int i){
	return st->a[i];
}


int STgetindex(ST st, Item item){
	int i = hash(GETname(item), st->M);
	while(full(st,i))
		if(CMPname(item, st->a[i]) == 0)
			return i;
		else
			i = (i+1) % st->M;
	return -1;
}

void STchange(ST st, Item item){
	int i = STgetindex(st, item);
	st->a[i] = item;
	return;
}


void STdisplay(ST st){
	int i=0;
	for(i=0;i<st->M;i++)
		if(full(st,i))
			ITEMprint(st->a[i]);
	return;
}