#ifndef COLLECTION_H
#define COLLECTION_H

#include "../document/document.h"

typedef struct collection Collection;

Collection *newCollection(char *);
void addDocument(Collection *, Document *);
void showDocuments(Collection *);

#endif
