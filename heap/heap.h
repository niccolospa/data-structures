#ifndef LB_HEAP_H
#define LB_HEAP_H

#include "Item.h"

typedef struct heap *Heap;

Heap HEAPinit(int);
void HEAPfill(Heap, Item);
void HEAPsort(Heap);
void HEAPdisplay(Heap);

#endif