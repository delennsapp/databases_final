/*
Developer: Delenn Sapp
Date: 11/28/2017
Document
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "document.h"
#include "../../dictionary/dictionary.h"
#include "../../scanner/scanner.h"

struct document
{
  int version;
  int sysID;
  int latest;
  Dictionary *fields;
};

Document *newDocument(int sysid) 
{
    Document *d = allocate(sizeof(Document));
    d->sysID = sysid;
    d->fields = newDictionary();
    return d;
}

int getDocVersion(Document *d)
{
    return d->version;
}

int getDocID(Document *d)
{
    char *v = getValue(d->fields, "DocID");
    if(v != NULL)
        return atoi(v);
    return -1;
}

int getSysID(Document *d)
{
    return d->sysID;
}

void setDocVersion(Document *d, int v)
{
    d->version = v;
    return;
}

void setDocLatest(Document *d, int l)
{
    d->latest = l;
    return;
}

int isLatest(Document *d)
{
    return d->latest;
}

int hasField(Document *d, char *f)
{
    if(containsKey(d->fields, f))
        return 1;
    return 0;
}

int getFieldValue(Document *d, char *f)
{
    char *v = getValue(d->fields, f);
    if(v != NULL)
        return atoi(v);
    return -1;
}

void addField(Document *d, char *k, char *v)
{
    if(strlen(k) > 0)
        addKVF(d->fields, strdup(k), strdup(v));
    return;
}

void showDocument(Document *d)
{
    printf("vn: %d ", d->version);
    printf("sysid: %d ", d->sysID);
    displayDictionary(d->fields);
    printf("\n");
}

void showDocumentWithFile(Document *d, FILE *results)
{
    printf("vn: %d ", d->version);
    fprintf(results, "vn: %d ", d->version);
    printf("sysid: %d ", d->sysID);
    fprintf(results, "sysid: %d ", d->sysID);
    displayDictionaryWithFile(d->fields, results);
    printf("\n");
    fprintf(results, "\n");
}

Document *createDocument(char *l, int sysid, int start)
{
    Document *d = newDocument(sysid);
    char key[255];
    char value[255];
    char ch;
    int i; 
    int j = 0;
    int onKey = 1;
    for(i = start; i<strlen(l); i++)
    {
        ch = l[i];
        if(ch == ':') {
            onKey = 0;
            key[j] = '\0';
            j = 0;
        }
        else if(ch == ' ')
        {
            value[j] = '\0';
            addField(d, key, value);
            memset(&key[0], 0, sizeof(key));
            memset(&value[0], 0, sizeof(value));
            onKey = 1;
            j = 0;
        }
        else if(onKey)
        {
            key[j] = l[i];
            ++j;
        }
        else
        {
            value[j] = ch;
            ++j;
        }
    }
    addField(d, key, value);
    return d;
}
