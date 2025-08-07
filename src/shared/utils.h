#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "entity.h"

Vector2 FromCenteredReturnTopLeftPosition(Entity *entity);
Vector2 FromCenteredReturnTopLeftPositionV(Vector2 position, Vector2 size);
Vector2 centeredPosition(Entity *entity);

#endif
