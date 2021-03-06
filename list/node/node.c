/*  
Developer: Delenn Sapp
Date: February 4, 2016
File containing a node structure with both next and previous pointers, as well as its accessors and setters.
*/

#include "node.h"
#include "../../io/utilities/utilities.h"
#include "../../scanner/scanner.h"

struct node
{
    void *data;
    struct node *next;
    struct node *previous;
};

Node *newNode(void)
{
    Node *node = allocate(sizeof(Node));
    node->data = NULL;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

void *getNodeData(Node *node)
{
    if(!node)
        return NULL;
    return node->data;
}

void setNodeData(Node *node, void *data)
{
    if(!node)
        return;
    node->data = data;
}

Node *getNodeNext(Node *node)
{
    if(!node)
        return NULL;
    return node->next;
}

void setNodeNext(Node *node, Node *next)
{
    if(!node)
        return;
    node->next = next;
}

Node *getNodePrevious(Node *node)
{
    if(!node)
        return NULL;
    return node->previous;
}

void setNodePrevious(Node *node, Node *previous)
{
    if(!node)
        return;
    node->previous = previous;
}

void freeNode(Node *node)
{
    if(!node)
        return;
    freeData(node->data);
    freeData(node);
}
