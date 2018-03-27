#ifndef LB_AVLBST_H
#define LB_AVLBST_H

#include "item.h"

typedef struct avlbinarysearchtree *AVLTree;

AVLTree AVLinit();
int AVLcount(AVLTree)
int AVLempty(AVLTree)
Item AVLmin(AVLTree)
Item AVLmax(AVLTree)
void AVLinsert(AVLTree,Item);
Item AVLsearch(AVLTree,Key);
void AVLdelete(AVLTree,Key);
Item AVLselect(AVLTree,int);
void AVLinorder(AVLTree);
void AVLpreorder(AVLTree);
void AVLpostorder(AVLTree);
Item AVLsucc(AVLTree,Key);
Item AVLpred(AVLTree,Key);

#endif