#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "list.h"

int main(){

	LArray A = LARRAYinit(10);
	int i;

	//LArray Test
	for(i=0;i<10;i++)
		LARRAYinsert(A,ITEMinit(10-i),i);
    //LARRAYbubblesort(A); //it works
    //LARRAYselectionsort(A); //it works
    //LARRAYinsertionsort(A); //it works
    //LARRAYshellsort(A); //it works
    //LARRAYcountingsort(A,11); //it works
    //LARRAYmergesort(A); //it works
    LARRAYquicksort(A); //it works
    if(LARRAYlinearsearch(A, ITEMinit(3))>=0) //it works
        printf("Linear Found!\n");
    if(LARRAYbinarysearch(A, ITEMinit(3))>=0) //it works
        printf("Binary Found!\n");
	for(i=0;i<10;i++)
		printf("%d ",ITEMget(LARRAYget(A,i)));
	printf("\n");

	//LSList
	LSList LS1 = LSListinit();
	LSList LS2 = LSListinit();
    for(i=0;i<10;i++){
        LSLISTinserttail(LS1,ITEMinit(i));
        LSLISTinserthead(LS2,ITEMinit(i));
    }
    printf("Count LS1: %d\n",LSLISTcount(LS1));
    printf("Count LS2: %d\n",LSLISTcount(LS2));
    printf("Search LS1 found!\n",LSLISTsearch(LS1,ITEMinit(3)));
    printf("Search LS2 found!\n",LSLISTsearch(LS2,ITEMinit(3)));
    LSLISTtraverse(LS1);
    LSLISTtraverse(LS2);

    //DSList
    LDList LD1 = LDListinit();
	LDList LD2 = LDListinit();
    for(i=0;i<10;i++){
        LDLISTinserttail(LD1,ITEMinit(i));
        LDLISTinserthead(LD2,ITEMinit(i));
    }
    printf("Count LD1: %d\n",LDLISTcount(LD1));
    printf("Count LD2: %d\n",LDLISTcount(LD2));
    printf("Search LD1 found!\n",LDLISTsearch(LD1,ITEMinit(3)));
    printf("Search LD2 found!\n",LDLISTsearch(LD2,ITEMinit(3)));
    LDLISTtraverse(LD1);
    LDLISTtraverse(LD2);

	return 0;
}
