#include <stdlib.h>
#include <string.h>
#include "st.h"

#define FNV_OFFSET_BASIS 2166136261
#define FNV_PRIME 16777619

struct symboltable { Item *a; int N; int M; };

int hash1(char *str, int M){
	int h=0, base=127, i;
	for(i=0;str[i]!='\0';i++)
		h = (base * h + str[i]) % M;
	return h;
}

int hash2(char *str, int M){
	int h=0, base=127, i;
	for(i=0;str[i]!='\0';i++)
		h = (base * h + str[i]);
	h = ((h % 97) + 1);
	return h;
}

int hashFNV(char *str, int M){
	int hash = FNV_OFFSET_BASIS;
	int i;
	for(i=0;i<strlen(str);i++){
		hash = hash ^ str[i];
		hash = hash * FNV_PRIME
	}
	hash = hash % M;
	return hash;
}

int hashU(char *str, int M){
	int hash, a = 31415, b = 27183, i;
	for(hash=0, i=0; str[i]!='\0'; i++, a = a*b%(M-1))
		h = (a*h + str[i]) % M;
	return h;
}

ST STinit(int maxN){
	ST st = malloc(sizeof(*st));
	st->N = 0;
	st->M = maxN;
	st->a = malloc(st->M * sizeof(Item));
	for(i=0;i<st->M;i++)
		st->a[i] = ITEMsetvoid();
	return st;
}

int STcount(ST st){
	return st->N;
}

int STempty(ST st){
	if(STcount(st)==0)
		return 1;
	return 0;
}

int full(ST st, int i){
	if(ITEMcheckvoid(st->a[i]))
		return 0;
	else
		return 1;
}

void STdisplay(ST st){
	int i;
	for(i=0;i<st->M;i++){
		printf("st->a[%d] = ", i);
		ITEMprint(st->a[i]);
		printf("\n");
	}
}

void STinsert(ST st, Item item){
	int i = hashFNV(ITEMtostring(item), st->M);
	int j = hash2(ITEMtostring(item), st->M);
	while(full(st, i))
		i = (i+j) % st->M;
	st->a[i] = item;
	st->N++;
}

Item STsearch(ST st, char *str){
	int i = hashFNV(str, st->M);
	int j = hash2(str, st->M);
	while(full(st,i))
		if(strcmp(str,ITEMtostring(st->a[i]))==0)
			return st->a[i];
		else
			i = (i+j)%st->M;
	return ITEMsetvoid();
}