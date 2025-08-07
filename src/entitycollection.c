#include "entitycollection.h"
#include <stdio.h>
#include <stdlib.h>

void InitEntityCollection(EntityCollection *collection)
{
    collection->head = NULL;
}

CollectionNode *CreateCollectionNode(Entity *entity)
{
    CollectionNode *node = malloc(sizeof(CollectionNode));
    node->next = NULL;
    node->prev = NULL;
    node->entity = entity;

    return node;
}

void AppendEntityCollection(EntityCollection *collection, Entity *entity)
{
    CollectionNode *newNode = CreateCollectionNode(entity);

    newNode->next = collection->head;
    if (collection->head != NULL)
        collection->head->prev = newNode;
    collection->head = newNode;
}

void FreeDeadEntitiesFromCollection(EntityCollection *collection)
{
    CollectionNode *curr = collection->head;

    while (curr != NULL)
    {
        Entity *currEntity = curr->entity;
        if (!currEntity->alive)
        {

            CollectionNode *toDelete = curr;
            curr = curr->next;
            FreeEntityFromEntityCollection(collection, toDelete);
            continue;
        }
        curr = curr->next;
    }
}

void FreeEntityFromEntityCollection(EntityCollection *collection, CollectionNode *node)
{
    if (collection->head == NULL || node == NULL)
        return;
    if (collection->head == node)
        collection->head = node->next;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    free(node->entity);
    free(node);
}

void FreeEntityCollection(EntityCollection *collection)
{
    CollectionNode *curr = collection->head;

    while (curr != NULL)
    {
        CollectionNode *temp = curr;
        curr = curr->next;
        free(temp->entity);
        free(temp);
    }

    collection->head = NULL;
}
