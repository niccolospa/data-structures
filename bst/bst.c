#include "bst.h"
#include "Item.h"
#include <stdlib.h>

typedef struct BSTnode *link;
struct BSTnode { Item item; link l; link r; };
struct binarysearchtree { link head; link z; };

link NEW(Item item, link l, link r){
	link x = malloc(sizeof(*x));
	x->item = item;
	x->l = l;
	x->r = r;
	return x;
}

BST BSTinit(){
	BST bst = malloc(sizeof(*bst));
	bst->head = NEW(ITEMsetvoid(), NULL, NULL);
	bst->z = bst->head;
	return bst;
}

Item searchR(link h, Key k, link z){
	if(h==z)
		return ITEMsetvoid();
	if(KEYcompare(k, KEYget(h->item))==0)
		return h->item;
	if(KEYcompare(k, KEYget(h->item))==-1)
		return searchR(h->, k, z);
	else
		return searchR(h->r, k, z);
}

Item BSTsearch(BST bst, Key k){
	return searchR(bst->head, k, bst->z);
}