#include "list.h"
#include <stdlib.h>

//Singly Linked List
struct singlylinkedlist { Item item; slink next; };

slink LSNEW(Item item, slink next){
	slink x = malloc(sizeof(*x));
	x->item = item;
	x->next = next;
	return x;
}
Item LSLISTgetitem(slink x){
	if(x == NULL)
		return NULL;
	return x->item;
}
slink LSHEAD(LSList L){
	return *L;
}

LSList LSLISTinit(){
	LSList L = malloc(sizeof(*L));
	return L;
}

int LSLISTcount(LSList L){
	int count=0;
	slink x = LSHEAD(L);
	if(x == NULL)
		return 0;
	for( ; x!=NULL ; x=x->next, count++ );
	return count;
}

void LSLISTtraverse(LSList L){
	slink x = LSHEAD(L);
	if(x == NULL)
		return;
	for( ; x->next!=NULL ; x=x->next ){
		//do something
	}
	return;
}

void LSLISTinserthead(LSList L, Item item){
	slink *head = L;
	*head = LSNEW(item,*head);
}

void LSLISTinserttail(LSList L, Item item){
	slink *head = L;
	slink x = *head;
	if(x == NULL)
		*head = LSNEW(item, NULL);
	else{
		for( ; x->next!=NULL; x=x->next);
			x->next = LSNEW(item, NULL);
	}
}

int LSLISTsearch(LSList L,Item item){
	slink x = LSHEAD(L);
	if(x == NULL)
		return 0;
	for( ; x->next!=NULL ; x=x->next)
		if( ITEMeq(item, x->item) )
			return 1;
	return 0;
}

void LSLISTdelete(LSList L,Item item){
	slink *head = L;
	slink t,p;
	if(*head == NULL)
		return;
	for( t=*head, p=NULL; t->next!=NULL ; p=t, t=t->next ){
		if( ITEMeq(item, t->item) ){
			if(t == *head)
				*head = t->next;
			else
				p->next = t->next;
			free(t);
			break;
		}
	}
	return;
}

//Double Linked List
struct doublelinkedlist { Item item; dlink prev; dlink next; };

dlink LDNEW(Item item, dlink prev, dlink next){
	dlink x = malloc(sizeof(*x));
	x->item = item;
	x->prev = prev;
	x->next = next;
	return x;
}
Item LDLISTgetitem(dlink x){
	if(x == NULL)
		return NULL;
	return x->item;
}
dlink LDHEAD(LDList L){
	return *L;
}

int LDLISTcount(LDList L){
	dlink x = LDHEAD(L);
	int count=0;
	if(x == NULL)
		return 0;
	for( ; x!=NULL ; x=x->next, count++ );
	return count;
}

void LDLISTtraverse(LDList L){
	dlink x = LDHEAD(L);
	if(x == NULL)
		return;
	for( ; x->next!=NULL ; x=x->next ){
		//do something
	}
	return;
}

void LDLISTinserthead(LDList L, Item item){
	dlink *head = L;
	*head = LDNEW(item,NULL,*head);
}

void LDLISTinserttail(LDList L,Item item){
	dlink *head = L;
	dlink t = *head;
	if(t == NULL)
		*head = LDNEW(item, NULL, *head);
	else{
		for( ; t->next!=NULL; t=t->next);
		t->next = LDNEW(item, t, NULL);
	}
}

int LDLISTsearch(LDList L, Item item){
	dlink x = LDHEAD(L);
	if(x == NULL)
		return 0;
	for( ; x->next!=NULL ; x=x->next )
		if( ITEMeq(item,x->item) )
			return 1;
	return 0;
}

void LDLISTdelete(LDList L,Item item){
	dlink *head = L;
	dlink t;
	if(*head == NULL)
		return;
	for( t=*head; t->next!=NULL ; t=t->next ){
		if( ITEMeq(item, t->item) ){
			if(t == *head){
				*head = t->next;
				t->next->prev = *head;
			}
			else{
				t->prev->next = t->next;
				t->next->prev = t->prev;
				
			}
			free(t);
			break;
		}
	}
	return;
}
