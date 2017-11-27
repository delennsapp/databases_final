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

Document *newDocument() 
{
    Document *d = allocate(sizeof(Document));
    d->fields = newDictionary();
    return d;
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
    displayDictionary(d->fields);
}

Document *createDocument(char *l)
{
    Document *d = newDocument();
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
