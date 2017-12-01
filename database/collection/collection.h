#ifndef COLLECTION_H
#define COLLECTION_H

#include "../document/document.h"
#include "../../array/array.h"

typedef struct collection Collection;

Collection *newCollection(char *, FILE *);
char *getCollectionName(Collection *);
void addDocument(Collection *, Document *);
void showDocuments(Collection *);
Array *filterByField(Collection *, char *);
Array *filterForLatest(Collection *, Array *);
Array *filterByNumberVersions(Collection *, Array *, int);
Array *filterByConditions(Collection *, char *);

#endif
