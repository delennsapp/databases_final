/*
Developer: Delenn Sapp
Date: February 4, 2016
File that includes various utility functions, such as allocate, and printing functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *alloc(size_t size)
{
    void *new = malloc(size);
    if(!new)
    {
        printf("Allocating the data type %zu failed\n", size);
        exit(1);
    }
    return new;
}

void printInt(int data)
{
    printf("%d ", data);
}

void printNewline(void)
{
    printf("\n");
}

void freeData(void *data)
{
    free(data);
}

char *dynamicCopy(const char *s)
{
    size_t len = strlen(s) + 1;
    char *d = alloc(len);
    strcpy(d, s);
    return d;
}
