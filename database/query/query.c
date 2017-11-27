/*
Developer: Delenn Sapp
Date: 11/27/2017
Query file
*/

#include "query.h"
#include "../../array/array.h"

struct query
{
    char *type;
    Array *condition;
    Array *field;
    Array *version;
};

struct count
{
    char *type;
    char *field;
    Array *version;
};

struct sort
{
    char *type;
    char *field;
};

struct insert
{
   char *type;
   int id;
};
