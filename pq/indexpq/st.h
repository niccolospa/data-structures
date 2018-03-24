#ifndef LB_ST_H
#define LB_ST_H

typedef struct symboltable *ST;

ST STinit(int);
int STsize(int);
int STinsert(ST,Item);
int STcount(ST);
int STempty(ST);
Item STgetitem(ST,int);
int STgetindex(ST,Item);
void STchange(ST,Item);
void STdisplay(ST);

#endif