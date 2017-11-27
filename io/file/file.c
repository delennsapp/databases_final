/*
Developer: Delenn Sapp
Date: Februrary 4, 2016
File that contains functions to read from a file.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utilities/utilities.h"

static int checkIfFileIsEmpty(FILE *fp, char *filename)
{
    /* attempts to pull a character from the file, if a character is found the file is not empty, 
    and the character is put back to allow for proper reading of the file. */
    int ch = fgetc(fp);
    if (ch == EOF)
    {
        fprintf(stderr, "File \"%s\" is empty. Please provide a file with appropriate data.\n", filename);
        exit(0);
    }
    ungetc(ch, fp);
    return 0;
}

/*
readInt written by John C. Lusth 
made static by Delenn Sapp
The module this function was pulled from can be downloaded from troll.cs.ua.edu/cs100/scanner.c
*/

static int readInt(FILE *fp)
{
    int x,result;
    result = fscanf(fp,"%d",&x);
    if (result == EOF)
    {
        return 0;
    }
    if (result == 0)
    {
        fprintf(stderr,"SCAN ERROR: attempt to read an integer failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(1);
    }
    return x;
}

FILE *openFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp)
    {
        fprintf(stderr, "File \"%s\" could not be opened for reading.\n", filename);
        exit(1);
    }
    checkIfFileIsEmpty(fp, filename);
    return fp;
}

void closeFile(FILE *fp)
{
    fclose(fp);
}

int readIntFromFile(FILE *fp)
{
    int data = readInt(fp);
    return data;
}
