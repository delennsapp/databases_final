/*
Developer: Delenn Sapp
Date: 11/27/2017
Collection 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection.h"
#include "../document/document.h"
#include "../../scanner/scanner.h"
#include "../../array/array.h"
#include "../../list/doublylinked/doublylinked.h"

struct collection
{
    char *name;
    FILE *fp;
    List *documents;
};

Collection *newCollection(char *n, FILE *f)
{
    Collection *c = allocate(sizeof(Collection));
    c->name = n;
    c->fp = f;
    c->documents = newList();
    return c;
}

char *getCollectionName(Collection *c)
{
    return c->name;
}

Array *filterByField(Collection *c, char *f)
{
    Array *a = newArray();
    Document *current = iterateList(c->documents);
    while(current != NULL)
    {
        if(hasField(current, f))
            append(a, current);
        current = iterateList(c->documents);
    }
    return a;
}

Array *filterForLatest(Collection *c, Array *a)
{
    Array *new = newArray();
    int i;
    for(i = 0; i < getArraySize(a); i++)
    {
        Document *d = getIndex(a, i);
        if(isLatest(d))
        {
            append(new, d);
        }
    }
    return new;
}

Array *filterByNumberVersions(Collection *c, Array *a, int v)
{
    int i;
    int j;
    Document *d1;
    Document *d2;
    Array *new = newArray();
    Array *latest = filterForLatest(c, a);
    for(i = 0; i < getArraySize(a); i++)
    {
        d1 = getIndex(a, i);
        if(isLatest(d1))
        {
            append(new, d1);
        }
        else {
            for(j = 0; j < getArraySize(latest); j++)
            {
                d2 = getIndex(latest, j);
                if(getDocID(d1) == getDocID(d2))
                {
                    if(getDocVersion(d1) > (getDocVersion(d2) - v))
                    {
                        append(new, d1);
                    }
                }
            }
        }
    }
    return new;
}

Array *parseCondition(char *c, char *s)
{
    char field[255];
    char operation[255];
    char value[255];
    int position = 0;
    int i;
    char ch;
    int j = 0;
    Array *a = newArray();

    for(i = 0; i < strlen(c); i++)
    {
        ch = c[i];
        if(position == 0)
        {
            if(ch == '=' || ch == '<' || ch == '>')
            {
                field[j] = '\0';
                position = 1;
                j = 0;
                operation[j] = ch;
                j++;
            }
            else
            {
                field[j] = ch;
                j++;
            }
        }
        else if(position == 1)
        {
            if(ch != '>' && ch != '<' && ch != '=')
            {
                operation[j] = '\0';
                j = 0;
                position = 2;
                value[j] = ch;
                j++;
            }
            else
            {
                operation[j] = ch;
                j++;
            }
        }
        else if(position == 2)
        {
            value[j] = ch;
            j++;
        }
    }
    value[j] = '\0';
    append(a, s);
    append(a, strdup(field));
    append(a, strdup(operation));
    append(a, strdup(value));
    return a;
}

Array *getCondition(char *cond, int s)
{
    char c[255];
    char str[255];
    int i;
    int j = 0;
    char ch;
    
    for(i = s; i < strlen(cond); i++)
    {
        ch = cond[i];
        if(ch == ' ') continue;
        else if(ch == ',')
        {
            j++;
            break;
        }
        else
        {
            c[j] = ch;
            j++;
        }
    }
    c[j] = '\0';
    sprintf(str, "%d", i+1);
    return parseCondition(strdup(c), strdup(str));
}

int meetsCondition(Document *d, char *f, char *o, char *v)
{
    int val = atoi(v);
    int vl;
    if(hasField(d, f))
    {
       vl = getFieldValue(d, f);
    }
    else 
        return 1;
    if(strcmp(o, "=") == 0)
        return (vl == val);
    if(strcmp(o, ">=") == 0)
        return (vl >= val);
    if(strcmp(o, "<=") == 0)
        return (vl <= val);
    if(strcmp(o, "<") == 0)
        return (vl < val);
    if(strcmp(o, ">") == 0)
        return (vl > val);
    if(strcmp(o, "<>") == 0)
        return (vl != val);
    return 0;
}

int hasAnyField(Document *d, List *conditions)
{
    Array *current;
    char *f;
    int hasFd = 0;
    
    current = iterateList(conditions);
    while(current != NULL)
    {
        f = getIndex(current, 1);
        if(hasField(d, f))
            hasFd = 1;
        current = iterateList(conditions);
    }
    return hasFd;
}

Array *meetsConditions(Array *all, List *conds)
{
    Array *new = newArray();
    int i;
    int meetsAll = 1;
    Array *current;
    for(i = 0; i < getArraySize(all); i++)
    {
        Document *d = getIndex(all, i);
        if(hasAnyField(d, conds))
        {
            current = iterateList(conds);
            while(current != NULL) {
                int mc = meetsCondition(d, getIndex(current, 1), getIndex(current, 2), getIndex(current, 3));
                if(!mc)
                    meetsAll = 0;
                current = iterateList(conds);
            }
            if(meetsAll)
            {
                append(new, d);
            }
        }
        meetsAll = 1;
    }
    return new;
}

Array *filterByConditions(Collection *c, char *conditions)
{
    int moreConditions = 1;
    int s = 0;
    Array *a = newArray();
    List *conds = newList();
    Document *current = iterateList(c->documents);
    while(current != NULL)
    {
        append(a, current);
        current = iterateList(c->documents);
    }
    if(strlen(conditions) == 0)
        return a;
    else 
    {
        while(moreConditions)
        {
            Array *cond = getCondition(conditions, s);
            addListNode(conds, cond);
            char *stopped = getIndex(cond, 0);
            s = atoi(stopped);
            if(strlen(conditions) <= s)
                moreConditions = 0;
        }
        return meetsConditions(a, conds);
    }
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
