#ifndef DOCUMENT_H
#define DOCUMENT_H


typedef struct document Document;

Document *createDocument(char *, int);
int getDocVersion(Document *);
int getDocID(Document *);
void setDocVersion(Document *, int);
void setDocLatest(Document *, int);
void showDocument(Document *);

#endif
