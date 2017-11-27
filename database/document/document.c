/*
Developer: Delenn Sapp
Date: 11/28/2017
Document
*/

#include <string.h>

#include "document.h"
#include "../../dictionary/dictionary.h"
#include "../../scanner/scanner.h"
#include "../collection/collection.h"

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
    Document *d = allocate(sizeof(Document))
    d->fields = newDictionary();
    return d;
}

void addDocument(char *l, Collection *c);
{
    Document *d = newDocument();
    char *current;
    char ch;
    int i; 
    int size = strlen(l);
    for(i = 0; i<size; i++)
    {
        ch = l[i];
        printf("%s ", ch);
    }
    printf("\n");
}

void parseDocFile(File *fp, Collection *c)
{
    char *line = readLine(fp);
    while(!feof(fp))
    {
        addDocument(line, c);
        ch = readLine(fp);
    }
    free(ch);
    fclose(fp);
    return;
}
    
}
