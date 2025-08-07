#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "engine.h"

typedef void (*CollisionHandler)(Engine *engine, Entity *a, Entity *b);

void UpdateCollisions(Engine *engine);
void InitCollisionSystem();
#endif
