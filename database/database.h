#ifndef DATABASE_H
#define DATABASE_H

#include "collection/collection.h"

typedef struct database Database;

Database *newDatabase(char *);
int getDBSysID(Database *d);
void incrementSysID(Database *d);
void addCollection(Database *, Collection *);
Collection *getCollection(Database *, char *);
void showCollections(Database *); 
void doQuery(Database *, char *);

#endif
