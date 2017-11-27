#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../collection/collection.h"

typedef struct document Document;

Document *newDocument();
void parseDocFile(FILE *, Collection *);

#endif
