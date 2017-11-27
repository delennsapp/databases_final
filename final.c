/*
Developer: Delenn Sapp
Date: 11/28/2017
Main file for databases final
*/
#include <stdio.h>
#include <stdlib.h>

#include "io/file/file.h"
#include "database/document/document.h"
#include "database/collection/collection.h"
#include "scanner/scanner.h"


void parseDocFile(FILE *fp, Collection *c)
{
    char *line = readLine(fp);
    while(!feof(fp))
    {
        Document * d = createDocument(line);
        addDocument(c, d);
        free(line);
        line = readLine(fp);
    }
    free(line);
    fclose(fp);
    return;
}

int main(void)
{
    FILE *data = openFile("data.txt");
    Collection *c = newCollection("final");
    parseDocFile(data, c);
    showDocuments(c);
    return 0;
}
