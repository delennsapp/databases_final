/*
File: array.c
Developer: Delenn Sapp
Date: October 22, 2016
Dynamically allocated array
*/

#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "../utilities/utilities.h"

#define DEFAULT_SIZE 8 

struct array
{
    void **array;
    int size;
    int currentIndex;
};

Array *newArray()
{
    Array *a = allocate(sizeof(Array));
    a->array = allocate(sizeof(void *) * DEFAULT_SIZE);
    a->size = DEFAULT_SIZE;
    a->currentIndex = 0;
    return a;
}

void freeArray(Array *a)
{
    free(a->array);
    free(a);
}

void append(Array *a, void *item)
{
    int index = a->currentIndex;
    if(index == a->size)
    {
        a->size = a->size * 2; 
        a->array = reallocate(a->array, sizeof(void *) * a->size);
    }
    a->array[index] = item;
    a->currentIndex += 1;
}

void *getIndex(Array *a, int index)
{
    return a->array[index];
}

int getArraySize(Array *a)
{
    return a->currentIndex;
}
