#include <stdlib.h>
#include <stdio.h>
#include "array.h"

struct array_s {
	void **v;
	int size,curr;
	size_t bytesNumber;
	int (*compare)(void*,void*);
};

typedef struct array_s *Array;

Array arrayInit(int size, int (*compare)(void* e1,void *e2)){
	Array a=malloc(sizeof(*a));
	a->v=malloc(size*sizeof(void*));
	a->size=size;
	a->curr=0;
	a->compare=compare;
}

void arrayInsert(Array a, void *element, int index){
	a->v[index]=element;
}

void *arrayGet(Array a, int index){
	return a->v[index];
}
