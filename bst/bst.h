#ifndef LB_BST_H
#define LB_BST_H

#include "Item.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
Item BSTmin(BST);
Item BSTmax(BST);
void BSTinsert_leafI(BST,Item);
void BSTinsert_leafR(BST,Item);
void BSTinsert_root(BST,Item);
Item BSTsearch(BST, Key);
void BSTsortinorder(BST);
void BSTsortpreorder(BST);
void BSTsortpostorder(BST);

#endif