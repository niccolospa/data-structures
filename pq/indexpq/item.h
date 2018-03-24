#ifndef LB_ITEM_H
#define LB_ITEM_H

#define MAXC 10

typedef struct item *Item;
typedef char *KEYname;
typedef int KEYprio;

Item ITEMscan();
Item ITEMsetvoid();
int ITEMcheckvoid(Item data);
void ITEMprint(Item data);
Item ITEMchange();

int CMPname(Item data1, Item data2);
KEYname GETname(Item data);
KEYprio GETprio(Item data);
int CMPprio(Item data1, Item data2);