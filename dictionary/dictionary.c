/*
Developer: Delenn Sapp
Date: 11/28/2017
Dynamic dictionary
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int containsKey(Dictionary *d, char *k)
{
    Array *a = d->array;
    int i;
    for(i = 0; i < getArraySize(a); i++)
    {

        KVF *kvf = getIndex(a, i);
        if(strcmp(kvf->key, k) == 0)
            return 1;
    }
    return 0;
}

void *getValue(Dictionary *d, char *k)
{
    Array *a = d->array;
    int i;
    for(i = 0; i < getArraySize(a); i++)
    {

        KVF *kvf = getIndex(a, i);
        if(strcmp(kvf->key, k) == 0)
            return  kvf->value;
    }
    return NULL;
}

int compare(KVF *one, KVF *two)
{
    return strcmp(one->key, two->key);
}

int partition(Array *a, int low, int high)
{
    KVF *pivot = getIndex(a, high);
    int i = (low - 1);
    int j;
    KVF *r;
    KVF *l;
    for(j = low; j < high; j++)
    {
        l = getIndex(a, j);
        if(compare(l, pivot) < 0)
        {
            i++;
            r = getIndex(a, i);
            setArray(a, j, r);
            setArray(a, i, l);
        }
    }
    l = getIndex(a, i+1);
    r = getIndex(a, high);
    setArray(a, i+1, r);
    setArray(a, high, l);
    return (i + 1);
}

void qsortDict(Array *a, int low, int high)
{
    if(low < high)
    {
        int p = partition(a, low, high);
        qsortDict(a, low, p-1);
        qsortDict(a, p+1, high);
    }
}

void displayDictionary(Dictionary *d)
{
    Array *a = d->array;
    int i;
    for(i = 0; i < getArraySize(a); i++)
    {
        KVF *kvf = getIndex(a, i);
        char *v = kvf->value;
        printf("%s: %s ", kvf->key, v);
    }
    return;
}

void addKVF(Dictionary *d, char *k, void *v)
{
    KVF *kvf = allocate(sizeof(KVF));
    kvf->key = k;
    kvf->value = v;
    append(d->array, kvf);
    qsortDict(d->array, 0, getArraySize(d->array) - 1);
    return;
}
