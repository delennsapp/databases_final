
#include "collection.h"
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


