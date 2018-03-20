#ifndef LB_ARRAY_H
#define LB_ARRAY_H

#include "Item.h"

typedef struct array_s *LArray;

//construction
LArray LARRAYinit(int);
void LARRAYfree(LArray);

//sort
void LARRAYbubblesort(LArray);
void LARRAYselectionsort(LArray);
void LARRAYinsertionsort(LArray);
void LARRAYshellsort(LArray);
void LARRAYcountingsort(LArray,int);
//void LARRAYheapsort(LArray);
//void LARRAYquicksort(LArray);
//void LARRAYmergesort(LArray);

//search
int LARRAYlinearsearch(LArray,Item);
int LARRAYbinarysearch(LArray,Item);

//utility
Item LARRAYget(LArray,int);
void LARRAYinsert(LArray,Item,int);

#endif