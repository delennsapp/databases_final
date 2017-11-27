/*
Developer: Delenn Sapp
Date: 11/28/2017
Dynamic dictionary
*/

#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "../array/array.h"
#include "../scanner/scanner.h"

#define DEFAULT_SIZE 8 

struct dictionary 
{
    Array *array;
};

struct kvf
{
    char *key;
    void *value;
};

Dictionary *newDictionary()
{
    Dictionary *d = allocate(sizeof(Dictionary));
    d->array = newArray();
    return d;
}

void addKVF(Dictionary *d, char *k, void *v)
{
    printf("Adding K: %s V: %s\n", k, va);
    KVF *kvf = allocate(sizeof(KVF));
    kvf->key = k;
    kvf->value = va;
    append(d->array, kvf);
    return;
}

void displayDictionary(Dictionary *d)
{
    Array *a = d->array;
    int i;
    for(i = 0; i < getArraySize(a); i++)
    {
        KVF *kvf = getIndex(a, i);
        char *v = kvf->value;
        printf("Key: %s Value: %s\n", kvf->key, v);
    }
    return;
}
