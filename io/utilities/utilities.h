#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

void *alloc(size_t);
void printInt(int);
void printNewline(void);
void freeData(void *);
char *dynamicCopy(const char *);

#endif
