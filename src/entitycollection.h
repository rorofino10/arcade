#ifndef EntityCollection_H
#define EntityCollection_H

#include "entity.h"

typedef struct CollectionNode
{
    Entity *entity;
    struct CollectionNode *next;
    struct CollectionNode *prev;
} CollectionNode;

typedef struct
{
    CollectionNode *head;
} EntityCollection;

void InitEntityCollection(EntityCollection *collection);
void AppendEntityCollection(EntityCollection *collection, Entity *entity);
void RemoveNthEntityCollection(EntityCollection *collection, int n);
Entity *GetNthEntityCollection(EntityCollection *collection, int n);

CollectionNode *FindCollectionNodeFromEntity(EntityCollection *collection, Entity *entity);

void FreeDeadEntitiesFromCollection(EntityCollection *collection);
void FreeEntityFromEntityCollection(EntityCollection *collection, CollectionNode *node);
void FreeEntityCollection(EntityCollection *collection);

#endif
