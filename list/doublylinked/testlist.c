/*
Developer: Delenn Sapp
Date: Feburary 4, 2016
Main test file for a doubly linked list
*/

#include <stdio.h>
#include <stdlib.h>

#include "doublylinked.h"

int main(void)
{
    int i, *h;
    List *list = newList();
    for(i = 0; i < 7; i++)
    {
        h = malloc(sizeof(int));
        *h = i;
        addListNode(list, h);
    }
    printList(list);
    removeListHead(list);
    printList(list);
    removeListTail(list);
    printList(list);
    freeList(list);
    return 0;
}

