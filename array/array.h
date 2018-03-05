#ifndef LB_ARRAY
#define LB_ARRAY

typedef struct array_s *Array;

Array arrayInit(int size, int (*compare)(void* e1,void *e2));
void arrayInsert(Array a, void *element, int index);
void *arrayGet(Array a, int index);

#endif
