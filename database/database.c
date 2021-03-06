/*
Developer: Delenn Sapp
Date: 11/29/2017
Database
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "collection/collection.h"
#include "document/document.h"
#include "../list/doublylinked/doublylinked.h"
#include "../array/array.h"
#include "../scanner/scanner.h"

struct database
{
    char *name;
    int sysid;
    List *collections;
};

Database *newDatabase(char *n)
{
    Database *d = allocate(sizeof(Database));
    d->name = n;
    d->sysid = 1;
    d->collections = newList();
    return d; 
}

void freeDatabase(Database *d)
{
    Collection *current = iterateList(d->collections);
    while(current != NULL)
    {
        freeCollection(current);
        current = iterateList(d->collections);
    }
    free(d);
    return;
}

int getDBSysID(Database *d)
{
    return d->sysid;
}

void incrementSysID(Database *d)
{
    d->sysid = d->sysid + 1;
    return;
}

void addCollection(Database *d, Collection *c)
{
    addListNode(d->collections, c);
}

int hasCollection(Database *d, char *n)
{
    Collection *current = iterateList(d->collections);
    int exists = 0;
    while(current != NULL)
    {
        if(strcmp(getCollectionName(current), n) == 0)
        {
            exists = 1;
        }
        current = iterateList(d->collections);
    }
    return exists; 
}

Collection *getCollection(Database *d, char *n)
{
    Collection *current = iterateList(d->collections);
    Collection *c = current;
    while(current != NULL)
    {
        if(strcmp(getCollectionName(current), n) == 0)
        {
            c = current;
        }
        current = iterateList(d->collections);
    }
    return c;
}

void showCollections(Database *d)
{
    Collection *current = iterateList(d->collections);
    while(current != NULL)
    {
        printf("Collection: %s\n\n", getCollectionName(current));
        showDocuments(current);
        printf("\n\n");
        current = iterateList(d->collections);
    }
    return;
}

Array *getValuesInBracket(char *l, int s)
{
    char field[255];
    char str[255];
    int i;
    int j = 0;
    char ch;
    Array *a = newArray();

    for(i = s; i < strlen(l); i++)
    {
        ch = l[i];
        if(ch == '[') continue;
        else if(ch == ']')
        {
            field[j] = '\0';
            break;
        }
        else
        {
            field[j] = ch;
            j++;
        }

    }
    append(a, strdup(field));
    sprintf(str, "%d", i+1);
    append(a, strdup(str));
    return a;
}

int partitionByField(Array *a, char *f, int low, int high)
{
    Document *pivot = getIndex(a, high);
    int i = (low - 1);
    int j;
    Document *l;
    Document *r;

    for(j = low; j < high; j++)
    {
        l = getIndex(a, j);
        if(getFieldValue(pivot, f) > getFieldValue(l, f))
        {
            i++;
            r = getIndex(a, i);
            setArray(a, j, r);
            setArray(a, i, l);
        }
    }
    l = getIndex(a, i+1);
    r = getIndex(a, high);
    setArray(a,i+1, r);
    setArray(a, high, l);
    return (i + 1);
}

void sortByField(Array *a, char *f, int low, int high)
{
    if(low < high)
    {
        int p = partitionByField(a, f, low, high);
        sortByField(a, f, low, p-1);
        sortByField(a, f, p+1, high);
    }
}

void sortByVersion(Array *a, int n)
{
    int i, j;
    Document *d1;
    Document *d2;
    for(i = 1; i < n; i++)
    {
        d1 = getIndex(a, i);
        j = i - 1;
        d2 = getIndex(a, j);
        while(j >= 0 && (getDocVersion(d1) > getDocVersion(d2)) && (getDocID(d1) == getDocID(d2)))
        {
            setArray(a, j+1, d2);
            j = j-1;
            d2 = getIndex(a, j);
        }
        setArray(a, j+1, d1);
    }
}

int skipComma(char *l, int s)
{
    int i;
    for(i = s; i < strlen(l); i++) 
    {
        if(l[i] == ',' || l[i] == ' ') 
            continue;
        else
            break;
    }
    return i;
}

char *getVersionSection(char *l, int s)
{
    char versions[255];
    int i;
    int j = 0;
    char ch;
    int hasBracket = 0;
    int modifiedVersions = 0;

    s = skipComma(l, s);

    for(i = s; i < strlen(l); i++)
    {
        ch = l[i];
        if(ch == '[')
        {
            hasBracket = 1;
            continue;
        }
        else if(ch == ']')
        {
            versions[j] = '\0';
            break;
        }
        else
        {
            versions[j] = ch;
            modifiedVersions = 1;
            j++;
        }

    }
    if(hasBracket == 0)
        return "latest";
    else if(modifiedVersions == 0)
        return "all";
    return strdup(versions);
}

Array *filterVersions(Array *a, Collection *c, char *l, int s)
{
    char *versionSection = getVersionSection(l, s);
    if(strcmp(versionSection, "all") == 0);
    else if(strcmp(versionSection, "latest") == 0)
        a = filterByNumberVersions(c, a, 1);
    else
        a = filterByNumberVersions(c, a, atoi(versionSection));
    return a;
}

Array *getFieldsArray(char *f)
{
    Array *new = newArray();
    int i;
    int j = 0;
    char ch;
    char field[255];
    
    for(i = 0; i < strlen(f) + 1; i++)
    {
        ch = f[i];
        if(ch == ' ') continue;
        if(ch == ',')
        {
            field[j] = '\0';
            j = 0;
            append(new, strdup(field));
        }
        else
        {
            field[j] = ch;
            j++;
        }
    }
    field[j] = '\0';
    append(new, strdup(field));
    return new;
}

void showFilteredResults(Array *a, Array *f, FILE *results, char *query)
{
    int i;
    int j;
    char *ch;
    int hasFd = 0;
    fprintf(results, "%s)\n", query);
    for(i = 0; i < getArraySize(a); i++)
    {
        Document *d = getIndex(a, i);

        for(j = 0; j < getArraySize(f); j++)
        {
            char *ch = getIndex(f, j);
            if(hasField(d, ch) || strcmp(ch, "sysid") == 0)
            {
                hasFd = 1;
            }
        }
        if(hasFd == 1)
        {
            printf("vn: %d ", getDocVersion(d));
            fprintf(results, "vn: %d ", getDocVersion(d));
            for(j = 0; j < getArraySize(f); j++)
            {
                ch = getIndex(f, j);
                if(strcmp(ch, "sysid") == 0) 
                {
                    printf("sysid: %d ", getSysID(d));
                    fprintf(results, "sysid: %d ", getSysID(d));
                }
            }
            for(j = 0; j < getArraySize(f); j++)
            {
                ch = getIndex(f, j);
                if(hasField(d, ch))
                {
                    printf("%s: %d ", ch, getFieldValue(d, ch));
                    fprintf(results, "%s: %d ", ch, getFieldValue(d, ch));
                }
            }
        }
        if(hasFd)
        {
            printf("\n");
            fprintf(results, "\n");
        }
        hasFd = 0;
    }
    if(getArraySize(a) > 0)
    {
        printf("\n");
        fprintf(results, "\n");
    }
    freeArray(a);
    freeArray(f);
    return;
}

void showResults(Array *a, FILE *results, char *query)
{
    int i;
    fprintf(results, "%s)\n", query);
    for(i = 0; i < getArraySize(a); i++)
    {
        Document *d = getIndex(a, i);
        showDocumentWithFile(d, results);
    }
    if(getArraySize(a) > 0)
    {
        printf("\n");
        fprintf(results, "\n");
    }
    freeArray(a);
    return;
}

void showCount(Array *a, char *f, FILE *results, char *query)
{
    fprintf(results, "%s)\n", query);
    printf("count_%s: %d\n\n",f, getArraySize(a));
    fprintf(results, "count_%s: %d\n\n",f, getArraySize(a));
    freeArray(a);
    return; 
}

void insert(Database *d, Collection *c, char *l, int stopped, FILE *results)
{
    Document *doc = createDocument(l, getDBSysID(d), stopped);
    incrementSysID(d);
    addDocument(c, doc);
    fprintf(results, "%s)\n", l);
    return;
}

void sort(Collection *c, char *l, int s, FILE *results)
{
    Array *field = getValuesInBracket(l, s);
    char *f = getIndex(field, 0);
    char *stopped = getIndex(field, 1);
    Array *a = filterByField(c, f);
    a = filterVersions(a, c, l, atoi(stopped));
    sortByField(a, f, 0, getArraySize(a) - 1);
    showResults(a, results, l);
    freeArray(field);
    return;
}

void count(Collection *c, char *l, int s, FILE *results)
{
    Array *field = getValuesInBracket(l, s);
    char *f = getIndex(field, 0);
    char *stopped = getIndex(field, 1);
    Array *a = filterByField(c, f);
    a = filterVersions(a, c, l, atoi(stopped));
    showCount(a, f, results, l);
    freeArray(field);
    return;
}

void query(Collection *c, char *l, int s, FILE *results)
{
    Array *a;
    char *fields = "";
    if((strlen(l) - s) == 0)
        a = filterByNumberVersions(c, buildArray(c), 1);
    else {
        Array *cond = getValuesInBracket(l, s); 
        char *conditions = getIndex(cond, 0);
        char *stopped = getIndex(cond, 1);
        a = filterByConditions(c, conditions);

        s = skipComma(l, atoi(stopped)); 
        Array *f = getValuesInBracket(l, s);
        fields = getIndex(f, 0);
        stopped = getIndex(f, 1);

        a = filterVersions(a, c, l, atoi(stopped));
    }
    sortByField(a,"DocID", 0, getArraySize(a) - 1);
    sortByVersion(a, getArraySize(a));
    if(strlen(fields) == 0)
        showResults(a, results, l);
    else
        showFilteredResults(a, getFieldsArray(fields), results, l);
    return;
}

void determineQuery(Database *d, char *l, int s, char *c, char *q, FILE *results)
{
    Collection *coll;
    int size = strlen(l);
    if(hasCollection(d, c))
        coll = getCollection(d, c);
    else
        return;
    if(l[size-1] == ')')
        l[size-1] = '\0';
    else
    {
        return;
    }
    if(strcmp(q, "insert") == 0)
    {
        insert(d, coll, l, s, results);
    }
    else if(strcmp(q, "sort") == 0)
    {
        sort(coll, l, s, results);
    }
    else if(strcmp(q, "count") == 0)
    {
        count(coll, l, s, results);
    }
    else if(strcmp(q, "query") == 0)
    {
        query(coll, l, s, results);
    }
    else printf("Error. %s not a recognized operation\n", q);
    return;
}

int skipWhitespace(char *l)
{
    int i;
    for(i = 0; i < strlen(l); i++) 
    {
        if(l[i] != ' ') break;
    }
    return i;
}

void doQuery(Database *d, char *l, FILE *results)
{
    char coll[255];
    char query[255];
    int onColl = 1;
    int stopped = 0;
    char ch;
    int i;
    int j = 0;

    int start = skipWhitespace(l);

    for(i = start; i < strlen(l); i++)
    {
        ch = l[i];
        if(ch == '.') 
        {
            onColl = 0;
            coll[j] = '\0';
            j = 0;
        }
        else if(ch == '(')
        {
            query[j] = '\0';
            stopped = i + 1;
            break;
        }
        else if(onColl)
        {
            coll[j] = ch;
            ++j;
        }
        else
        {
            query[j] = ch;
            ++j;
        }
    }
    determineQuery(d, l, stopped, strdup(coll), strdup(query), results);
    return;
}
