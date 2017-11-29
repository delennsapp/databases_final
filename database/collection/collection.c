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

int getVersionNumber(List *docs, Document *d)
{
    int version = 1;
    Document *current = iterateList(docs);
    while(current != NULL)
    {
        if(getDocID(current) == getDocID(d)) 
        {
            setDocLatest(current, 0); 
            ++version;
        }
        current = iterateList(docs);
    }
    return version;
}

void addDocument(Collection *c, Document *d)
{
    setDocVersion(d, getVersionNumber(c->documents, d));
    setDocLatest(d, 1); 
    addListNode(c->documents, d);
}

void showDocuments(Collection *c)
{
    Document *current = iterateList(c->documents);
    while(current != NULL)
    {
        showDocument(current);
        printf("\n");
        current = iterateList(c->documents);
    }
    return;
}
