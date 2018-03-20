#ifndef LB_ITEM_H
#define LB_ITEM_H

//Item : int
typedef int *Item;

//construction
Item ITEMinit(int);
void ITEMfree(Item);

//utility
void ITEMset(Item,int);
int ITEMget(Item);

//comparison
int ITEMless(Item,Item);
int ITEMgreat(Item,Item);
int ITEMeq(Item,Item);

#endif