#include "Item.h"
#include <stdlib.h>

//construction
Item ITEMinit(int x){
	Item item = malloc(sizeof(*item));
	*item = x;
	return item;
}

void ITEMfree(Item item){
	free(item);
}

//utility
void ITEMset(Item item, int x){
	*item = x;
}

int ITEMget(Item item){
	return *item;
}

//comparison
int ITEMless(Item a, Item b){
	if(*a < *b)
		return 1;
	return 0;
}

int ITEMgreat(Item a, Item b){
	if(*a > *b)
		return 1;
	return 0;
}

int ITEMeq(Item a, Item b){
	if(*a == *b)
		return 1;
	return 0;
}
