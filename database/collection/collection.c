/*
Developer: Delenn Sapp
Date: 11/27/2017
Collection 
*/

#include <stdio.h>
#include <stdlib.h>

#include "collection.h"
#include "../document/document.h"
#include "../../scanner/scanner.h"
#include "../../list/doublylinked/doublylinked.h"

struct collection
{
    char *name;    
    List *documents;
};

Collection *newCollection(char *n)
{
    Collection *c = allocate(sizeof(Collection));
    c->name = n;
    c->documents = newList();
    return c;
}

void addDoc(Collection *c, Document *d)
{
    addListNode(c->documents, d);
}
