#include "entitycollection.h"
#include <stdio.h>
#include <stdlib.h>

void InitEntityCollection(EntityCollection *collection)
{
    collection->head = NULL;
}

void AppendEntityCollection(EntityCollection *collection, Entity *entity)
{
    CollectionNode *newNode = malloc(sizeof(CollectionNode));

    newNode->entity = entity;
    newNode->next = collection->head;
    collection->head = newNode;
}

void FreeEntityCollection(EntityCollection *collection)
{
    CollectionNode *curr = collection->head;

    while (curr != NULL)
    {
        CollectionNode *temp = curr;
        curr = curr->next;
        free(temp);
    }

    collection->head = NULL;
}
