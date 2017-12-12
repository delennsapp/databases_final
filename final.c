/*
Developer: Delenn Sapp
Date: 11/28/2017
Main file for databases final
*/
#include <stdio.h>
#include <stdlib.h>

#include "io/file/file.h"
#include "database/database.h"
#include "database/document/document.h"
#include "database/collection/collection.h"
#include "scanner/scanner.h"


void parseDocFile(FILE *fp, Collection *c, Database *db)
{
    char *line = readLine(fp);
    while(!feof(fp))
    {
        Document *d = createDocument(line, getDBSysID(db), 0);
        incrementSysID(db);
        addDocument(c, d);
        free(line);
        line = readLine(fp);
    }
    free(line);
    return;
}

void parseQueryFile(FILE *fp, Database *db, FILE *results)
{
    char *line = readLine(fp);
    while(!feof(fp))
    {
        doQuery(db, line, results);
        free(line);
        line = readLine(fp);
    }
    free(line);
    return;
}

int main(void)
{
    Database *db = newDatabase("db");
    FILE *data = openFile("data.txt");
    FILE *query = openFile("queries.txt");
    FILE *results = fopen("ldsapp.txt", "w");
    Collection *c = newCollection("final", data);
    addCollection(db, c);
    parseDocFile(data, c, db);
    parseQueryFile(query, db, results);
    fclose(data);
    fclose(query);
    fclose(results);
    freeDatabase(db);
    return 0;
}
