#ifndef DICTIONARY_H
#define DICTIONARY_H 


typedef struct dictionary Dictionary;
typedef struct kvf KVF;

Dictionary *newDictionary();
void addKVF(Dictionary *, char *, void *);
void displayDictionary(Dictionary *);
void displayDictionaryWithFile(Dictionary *, FILE *);
int containsKey(Dictionary *, char *);
void *getValue(Dictionary *, char *);
void freeDictionary(Dictionary *);

#endif
