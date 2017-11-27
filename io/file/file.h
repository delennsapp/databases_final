#ifndef FILE_H
#define FILE_H

FILE *openFile(char *);
void closeFile(FILE *);
int readIntFromFile(FILE *fp);

#endif
