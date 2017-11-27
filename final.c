/*
Developer: Delenn Sapp
Date: 11/28/2017
Main file for databases final
*/

#include "io/file/file.h"
#include "database/document/document.h"
#include "database/collection/collection.h"

int main(void)
{
    FILE *data = openFile("data.txt");
    Collection *c = newCollection("final");
    parseDocFile(data, c);
    return 0;
}
