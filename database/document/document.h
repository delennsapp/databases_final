#ifndef DOCUMENT_H
#define DOCUMENT_H


typedef struct document Document;

Document *createDocument(char *, int, int);
int getDocVersion(Document *);
int getDocID(Document *);
int getSysID(Document *);
void setDocVersion(Document *, int);
void setDocLatest(Document *, int);
void showDocument(Document *);
int hasField(Document *, char *);
int getFieldValue(Document *, char *);
int isLatest(Document *);

#endif
