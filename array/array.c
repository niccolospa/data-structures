#include "array.h"
#include <stdlib.h>

struct array_s { Item *v; int n; };

//construction
LArray LARRAYinit(int n){
	LArray A = malloc(sizeof(*A));
	A->v = malloc(n*sizeof(Item));
	A->n = n;
	return A;
}

void LARRAYfree(LArray A){
	free(A->v);
	free(A);
}

//sort
/*
Bubble Sort:
- Complexity: n^2
- Iterative
- Stable
- In-place
- Exchange sort
Every iterations compare two adjacent Items
and move the greatest after the other. This
brings the maximum Item at the right for
each iteration.
*/
void LARRAYbubblesort(LArray A){
	int i,j;
	Item tmp;
	for(i=0;i<A->n-1;i++){
		for(j=0;j<A->n-i-1;j++){
			if(ITEMgreat(A->v[j],A->v[j+1])){
				tmp = A->v[j];
				A->v[j] = A->v[j+1];
				A->v[j+1] = tmp;
			}
		}
	}
	return;
}

/*
Selection Sort:
- Complexity: n^2
- Iterative
- Unstable
- In-place
Every iteration finds the minimum Item and
moves it to the left.
*/
void LARRAYselectionsort(LArray A){
	int i,j,min;
	Item tmp;
	for(i=0;i<A->n-1;i++){
		min = i;
		for(j=i+1;j<A->n;j++){
			if(ITEMless(A->v[j],A->v[min])){
				min = j;
			}
		}
		tmp = A->v[i];
		A->v[i] = A->v[min];
		A->v[min] = tmp;
	}
	return;
}

/*
Insertion Sort:
- Complexity: n^2
- Iterative
- Stable
- In-place
Every iteration picks one Item and "inserts" it
into on the left in the correct position, so that
the left side of the vector is always ordered.
*/
void LARRAYinsertionsort(LArray A){
	int i,j;
	Item tmp;
	for(i=1;i<A->n;i++){
		tmp = A->v[i];
		j = i-1;
		while(j>=0 && ITEMless(tmp,A->v[j])){
			A->v[j+1] = A->v[j];
			j--;
		}
		A->v[j+1] = tmp;
	}
	return;
}
/*
Shell Sort:
- Complexity:
- Iterative
- Unstable
- In-place
Define a decreasing sequence, and for each number h
in that sequence it sorts sequences of elements
at a distance of h (using InsertionSort).
The sequence terminates with 1 and choosing different
ones can impact performance.
Knuth - n^(3/2)
Seq - n^(4/3)
Sedgewick - ?
*/
void LARRAYshellsort(LArray A){
	int Knuth[5]={1,4,13,40,121}; //h = 3*h+1
	int Seq[5]={1,8,23,77,281}; //h = 4^(i+1) + 3*2^i + 1
	int Sedgewick[5]={1,5,19,41,109};
	int i,j,k,h;
	Item tmp;
	for(i=4;i>=0;i--){
		h = Sedgewick[i];
		for(j=h;j<A->n;j++){
			tmp = A->v[j];
			k = j;
			while(k>=h && ITEMless(tmp,A->v[k-h])){
				A->v[k] = A->v[k-h];
				k -= h;
			}
			A->v[k] = tmp;
		}
	}
	return;
}

/*
Counting Sort:
- Complexity: n
- Iterative
- Stable
- Not in-place
This sort uses array B for the result and
array C for occurrences. Numbers must be
in the [0,k-1] interval. Every Item is placed
in the right spot by counting how many Items
are lesser than that.
*/
void LARRAYcountingsort(LArray A, int k){
	int i;
	int *B = malloc(A->n * sizeof(int));
	int *C = malloc(k * sizeof(int));
	for(i=0;i<k;i++)
		C[i] = 0;
	for(i=0;i<A->n;i++)
		C[ITEMget(A->v[i])]++;
	for(i=1;i<k;i++)
		C[i] += C[i-1];
	for(i=0;i<A->n;i++){
		B[ C[ITEMget(A->v[i])]-1 ] = ITEMget(A->v[i]);
		C[ITEMget(A->v[i])]--;
	}
	for(i=0;i<A->n;i++){
        ITEMset(A->v[i],B[i]);
	}
}

/*
Quick Sort:
- Complexity: n log n (n^2 worst case, very unlikely)
- Recursive
- Unstable
- In-place
Select a "pivot" Item; then every Item smaller than
that, is moved to its left; every bigger one is moved
to its right. Then quicksort is applied to each
sub-array.
Partition can be made in several ways. I use the
"Partition à la Hoare".
*/
void LQuickSort(LArray A, int l, int r);
void LSwap(LArray A, int n1, int n2);
int partition(LArray A, int l, int r);
void LARRAYquicksort(LArray A){
    LQuickSort(A, 0, A->n-1);
}
void LQuickSort(LArray A, int l, int r){
    int q;
    if(r<=l)
        return;
    q = partition(A, l, r);
    LQuickSort(A, l, q-1);
    LQuickSort(A, q+1, r);
    return;
}
void LSwap(LArray A, int n1, int n2){
    Item tmp;
    tmp = A->v[n1];
    A->v[n1] = A->v[n2];
    A->v[n2] = tmp;
    return;
}
int partition(LArray A, int l, int r){
    int i=l-1, j=r;
    Item x = A->v[r];
    for( ; ; ){
        while(ITEMless(A->v[++i],x) && i<r);
        while(ITEMgreat(A->v[--j],x) && j>l);
            if(j<l)
        if(j==l) break;
        if(i>=j) break;
        LSwap(A,i,j);
    }
    LSwap(A,i,r);
    return i;
}

/*
Merge Sort:
- Complexity - n log n
- Recursive
- Stable
- Not in-place
This sort uses a temporary B array. For each
recursive call, MergeSort is applied to half
of the initial array, until the termination
case (array of 1 element).
The merging operation works by taking elements
from one of the two sub-arrays by comparing them.
*/
void LMergeSort(LArray A, Item *B, int l, int r);
void LMerge(LArray A, Item *B, int l, int q, int r);
void LARRAYmergesort(LArray A){
    Item *B = malloc(A->n * sizeof(Item));
    LMergeSort(A,B,0,A->n-1);
    free(B);
}
void LMergeSort(LArray A, Item *B, int l, int r){
    int q = (l+r)/2;
    if(r<=l)
        return;
    LMergeSort(A,B,l,q);
    LMergeSort(A,B,q+1,r);
    LMerge(A,B,l,q,r);
}
void LMerge(LArray A, Item *B, int l, int q, int r){
    int i,j,k;
    i = l;
    j = q+1;
    for(k=l;k<=r;k++){
        if(i > q)
            B[k]=A->v[j++];
        else if (j > r)
            B[k]=A->v[i++];
        else if (ITEMless(A->v[i],A->v[j]) || ITEMeq(A->v[i],A->v[j]))
            B[k]=A->v[i++];
        else
            B[k]=A->v[j++];
    }
    for(k=l;k<=r;k++)
        A->v[k]=B[k];
    return;
}


//search
int LARRAYlinearsearch(LArray A, Item item){
	int i;
	for(i=0;i<A->n;i++)
		if(ITEMeq(A->v[i],item))
			return i;
	return -1;
}

int LARRAYbinarysearch(LArray A, Item item){
	int l,r,m;
	l = 0;
	r = A->n-1;
	while(l<=r){
		m = (l+r)/2;
		if(ITEMeq(item, A->v[m]))
			return m;
		else if(ITEMless(item, A->v[m]))
			r = m-1;
		else
			l = m+1;
	}
	return -1;
}

//utility
Item LARRAYget(LArray A, int index){
	return A->v[index];
}

void LARRAYinsert(LArray A, Item item, int index){
	A->v[index]=item;
}
