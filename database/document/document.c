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
  int DocID;
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
    return d->DocID;
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

void addField(Document *d, char *k, char *v)
{
    if(strcmp(k, "DocID") == 0)
    {
        int val = atoi(v);
        d->DocID = val;
    }
    else
    {
        addKVF(d->fields, strdup(k), strdup(v));
    }
    return;
}

void showDocument(Document *d)
{
    printf("DocID: %d\n", d->DocID);
    printf("SysID: %d\n", d->sysID);
    printf("Version: %d\n", d->version);
    printf("Latest: ");
    if(d->latest) printf("yes\n");
    else printf("no\n");
    displayDictionary(d->fields);
}

Document *createDocument(char *l, int sysid)
{
    Document *d = newDocument(sysid);
    char key[255];
    char value[255];
    char ch;
    int i; 
    int j = 0;
    int onKey = 1;
    int size = strlen(l);
    for(i = 0; i<size; i++)
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
