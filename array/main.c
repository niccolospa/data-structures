#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main(){
	LArray A = LARRAYinit(10);
	int i;
	for(i=0;i<10;i++)
		LARRAYinsert(A,ITEMinit(10-i),i);

    //LARRAYbubblesort(A); //it works
    //LARRAYselectionsort(A); //it works
    //LARRAYinsertionsort(A); //it works
    //LARRAYshellsort(A); //it works
    LARRAYcountingsort(A,11); //it works

    if(LARRAYlinearsearch(A, ITEMinit(3))>=0) //it works
        printf("Linear Found!\n");
    if(LARRAYbinarysearch(A, ITEMinit(3))>=0) //it works
        printf("Binary Found!\n");

	for(i=0;i<10;i++)
		printf("%d ",ITEMget(LARRAYget(A,i)));
	printf("\n");
	return 0;
}
