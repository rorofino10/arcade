#ifndef Entity_H
#define Entity_H

#include "raylib.h"

#define PLAYER_SPEED 100.0f

#define BULLET_SPEED 1000.0f

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum
{
    BULLET,
    ENEMY,
    PLAYER_CONTROLLED,
} EntityType;

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    EntityType type;
} Entity;

#endif
