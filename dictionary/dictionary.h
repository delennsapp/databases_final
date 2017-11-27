#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct array Array;

Array *newArray();
void append(Array *, void *);
void *getIndex(Array *, int);
int getArraySize(Array *);
void freeArray(Array *);

#endif
