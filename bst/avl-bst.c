#include <stdlib.h>
#include "bst.h"

typedef struct avl_node *link;
struct avl_node { Item item; link p; link l; link r; int N; int height; };
struct avlbinarysearchtree { link head; int N; link z; };

link NEW(Item item, link p, link l, link r, int N, int height){
	link x = malloc(sizeof(*x));
	x->item = item;
	x->p = p;
	x->l = l;
	x->r = r;
	x->N = N;
	return x;
}

int maxNumber(int a, int b){
	if(a > b)
		return a;
	return b;
}

int getBalance(link h){
	if(h == NULL)
		return 0;
	return h->left->height - h->right->height;
}

AVLTree AVLinit(){
	AVLTree avl = malloc(sizeof(*avl));
	avl->head = NEW(ITEMsetvoid(), NULL, NULL, NULL, 0, 0);
	avl->z = avl->head;
	avl->N = 0;
	return avl;
}	
	
int AVLcount(AVLTree avl){
	return avl->N;
}

int AVLempty(AVLTree avl){
	if(AVLcount(avl) == 0)
		return 1;
	return 0;
}

Item minR(link h, link z){
	if(h == z)
		return ITEMsetvoid();
	if(h->l == z)
		return h->item;
	return minR(h->l, z);
}

Item AVLmin(AVLTree avl){
	if(avl == NULL)
		return ITEMsetvoid();
	return minR(avl->head, avl->z);
}

Item maxR(link h, link z){
	if(h == z)
		return ITEMsetvoid();
	if(h->r == z)
		return h->item;
	return maxR(h->r, z);
}

Item AVLmax(AVLTree avl){
	if(avl == NULL)
		return ITEMsetvoid();
	return maxR(avl->head, avl->z);
}

link rotR(link h){
	link x = h->l;
	h->l = x->r;
	x->r->p = h;
	x->r = h;
	x->p = h->p;
	h->p = x;
	x->N = h->N;
	h->N = h->l->N + h->r->N + 1;
	h->height = maxNumber(h->l->height, h->r->height) + 1;
	x->height = maxNumber(x->l->height, x->r->height) + 1;
	return x;
}

link rotL(link h){
	link x = h->r;
	h->r = x->l;
	x->l->p = h;
	x->l = h;
	x->p = h->p;
	h->p = x;
	x->N = h->N;
	h->N = h->l->N + h->r->N + 1;
	h->height = maxNumber(h->l->height, h->r->height) + 1;
	x->height = maxNumber(x->l->height, x->r->height) + 1;
	return x;
}

link insertR(link h, Item item, link z){
	int balance;
	if(h == z)
		return NEW(item, h->p, z, z, 1, 1);
	if(ITEMless(item, h->item))
		h->l = insertR(h->l, item, z);
	else
		h->r = insertR(h->r, item, z);
	(h->N)++;
	h->height = maxNumber(h->l->height, h->r->height) + 1;
	balance = getBalance(h);
	if(balance > 1 && ITEMless(item, h->l->item))
		return rotR(h);
	if(balance < -1 && ITEMgreat(item, h->r->item))
		return rotL(h);
	if(balance > 1 && ITEMgreat(item, h->l->item)){
		h->l = rotL(h->l);
		return rotR(h);
	}
	if(balance < -1 && ITEMless(item, h->r->item){
		h->r = rotR(h->r);
		return rotL(h);
	}
	return h;
}

void AVLinsert(AVLTree avl, Item item){
	if(avl == NULL)
		return;
	avl->head = insertR(avl->head, item, avl->z);
	avl->N++;
}

Item searchR(link h, Key k, link z){
	if(h == z)
		return ITEMsetvoid();
	if(KEYcompare(k, KEYget(h->item)) == 0)
		return h->item;
	else if (KEYcompare(k, KEYget(h->item)) < 0)
		return searchR(h->l, k, z);
	else
		return searchR(h->r, k, z);
}
	
Item AVLsearch(AVLTree avl, Key k){
	if(avl == NULL)
		return ITEMsetvoid();
	return searchR(avl->head, k, avl->z);
}

link partR(link h, int k, link z){
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
	a->p = b;
	b->N = a->N + b->r->N + 1;
	return b;

link deleteR(link h, Key k, link z){
	link y, p;
	int balance;
	if(h == z)
		return;
	if(KEYcompare(h, KEYget(h->item)) < 0)
		h->l = deleteR(h->l, k, z);
	if(KEYcompare(h, KEYget(h->item)) > 0)
		h->r = deleteR(h->r, k, z);
	(h->N)--;
	if(KEYcompare(h, KEYget(h->item)) == 0){
		y = h;
		p = h->p;
		h = joinLR(h->l, h->r, z);
		h->p = p;
		free(y);
	}
	h->height = maxNumber(h->l->height, h->r->height);
	balance = getBalance(h);
	if(balance > 1 && getBalance(h->l) >= 0)
		return rotR(h);
	if(balance < -1 && getBalance(h->r) < 0)
		return rotL(h);
	if(balance > 1 && getBalance(h->l) < 0){
		h->l = rotL(h->l);
		return rotR(h);
	if(balance < -1 && getBalance(h->r) >=0){
		h->r = rotR(h->r);
		return rotL(h);
	}
	return h;
}

void AVLdelete(AVLTree avl, Key k){
	if(avl == NULL)
		return;
	deleteR(avl->head, k, avl->z);
	avl->N--;
}

Item selectR(link h, int k, link z){
	int t;
	if(h == z)
		return ITEMsetvoid();
	t = h->l->N;
	if(t > k)
		return selectR(h->l, k, z);
	if(t < k)
		return selectR(h->r, k-t-1, z);
	return h->item;

Item AVLselect(AVLTree avl, int k){
	if(avl == NULL)
		return ITEMsetvoid();
	return selectR(avl->head, k, avl->z);
}

void inorderR(link h, link z){
	if(h == z)
		return;
	inorderR(h->l, z);
	//do something
	inorderR(h->r, z);
	return;
}

void AVLinorder(AVLTree avl){
	if(avl == NULL)
		return;
	inorderR(avl->head, avl->z);
}

void preorderR(link h, link z){
	if(h == z)
		return;
	//do something
	preorderR(h->l, z);
	preorderR(h->r, z);
	return;
}

void AVLpreorder(AVLTree avl){
	if(avl == NULL)
		return;
	preorderR(avl->head, avl->z);
}

void postorderR(link h, link z){
	if(h == z)
		return;
	postorderR(h->l, z);
	postorderR(h->r, z);
	//do something
	return;
}

void AVLpostorder(AVLTree avl){
	if(avl == NULL)
		return;
	postorderR(avl->head, avl->z);
}

Item searchSucc(link h, Key k, link z){
	link p;
	if(h == z)
		return ITEMsetvoid();
	if(KEYcompare(k, KEYget(h->item)) == 0){
		if(h->r != z)
			return minR(h->r, z);
		else{
			p = h->p;
			while(p != z && h == p->r){
				h = p;
				p = p->p;
			}
			return p->item;
		}
	}
	if(KEYcompare(k, KEYget(h->item)) < 0)
		return searchSucc(h->l, k, z);
	else
		return searchSucc(h->r, k, z);
}

Item AVLsucc(AVLTree avl, Key k){
	if(avl == NULL)
		return ITEMsetvoid();
	return searchSucc(avl->head, k, avl->z);
}

Item searchPred(link h, Key k, link z){
	link p;
	if(h == z)
		return ITEMsetvoid();
	if(KEYcompare(k, KEYget(h->item)) == 0){
		if(h->l != z)
			return maxR(h->l, z);
		else{
			p = h->p;
			while( p != z && h == p->l ){
				h = p;
				p = p->p;
			}
			return p->item;
		}
	}
	if(KEYcompare(k, KEYget(h->item)) < 0)
		return searchPred(h->l, k, z);
	if(KEYcompare(k, KEYget(h->item)) > 0)
		return searchPred(h->r, k, z);
}

Item AVLpred(AVLTree avl, Key k){
	if(avl == NULL)
		return ITEMsetvoid();
	return searchPred(avl->head, k, avl->z);
}