/* 
Developer: Delenn Sapp
Date: Februrary 4, 2016
File containing a doubly linked list structure, as well as its accessors and setters.
*/

#include "doublylinked.h"
#include "../node/node.h"
#include "../../io/utilities/utilities.h"
#include "../../scanner/scanner.h"

struct list
{
    Node *head;
    Node *tail;
    Node *current;
};

List *newList(void)
{
    List *list = allocate(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void addListNode(List *list, void *data)
{
    Node *node = newNode();
    setNodeData(node, data);
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        setNodePrevious(node, list->tail);
        setNodeNext(list->tail, node);
        list->tail = node;
    }
}

void *peekListHead(List *list)
{
    if(list->head == NULL)
        return NULL;
    return getNodeData(list->head);
}

void *peekListTail(List *list)
{
    if(list->head == NULL)
        return NULL;
    return getNodeData(list->tail);
}
    
void removeListHead(List *list)
{
    Node *current = list->head;
    setNodePrevious(getNodeNext(list->head), NULL);
    list->head =  getNodeNext(list->head);
    freeData(current);
}

void removeListTail(List *list)
{
    Node *current = list->tail;
    list->tail = getNodePrevious(list->tail);
    setNodeNext(list->tail, NULL);
    freeData(current);
}

void *iterateList(List *list)
{
    list->current = list->current != NULL ? getNodePrevious(list->current) : list->tail;
    return getNodeData(list->current);
}

void printList(List *list)
{
    Node *current = list->head;
    while(current != NULL)
    {
        printInt(*(int *)getNodeData(current));
        current = getNodeNext(current);
    }
    printNewline();
}

void freeList(List *list)
{
    Node *current = list->head;
    while(current != NULL)
    {
        freeNode(current);
        current = getNodeNext(current);
    }
    freeData(list);
}
