#ifndef Entity_H
#define Entity_H

#include "raylib.h"

#define DEFAULT_PLAYER_SPEED 100.0f

#define DEFAULT_PLAYER_WIDTH 50
#define DEFAULT_PLAYER_HEIGHT 50

#define DEFAULT_ENEMY_SPEED 25.0f
#define DEFAULT_ENEMY_WIDTH 50
#define DEFAULT_ENEMY_HEIGHT 50

#define DEFAULT_BULLET_SPEED 1000.0f
#define DEFAULT_BULLET_SIZE 5
#define DEFAULT_BULLET_COLOR BLACK

#define DEFAULT_EXPLOSION_WIDTH 50
#define DEFAULT_EXPLOSION_HEIGHT 50

#define POWER_UP_LIFETIME 2.0f

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
    RED_ENEMY,
    BLUE_ENEMY,
    PLAYER_CONTROLLED,
    EXPLOSION,
    POWER_UP,
} EntityType;

typedef struct
{
    float lifetime;
} ExplosionAttributes;

typedef struct
{
    float powerUpLifetime;
} PlayerAttributes;

typedef struct
{
    float speed;
    Vector2 size;
    Color color;
    union
    {
        ExplosionAttributes explosion;
        PlayerAttributes player;
    } entitySpecificAttributes;
} EntityAttributes;

typedef struct Entity
{
    Vector2 position;
    Vector2 velocity;
    EntityType type;
    EntityAttributes attributes;
    bool alive;
} Entity;

Entity *DefaultPlayer();
Entity *DefaultEnemy();
Entity *DefaultPowerUp();
Entity *DefaultBulletFromEntity(Entity *entity, Vector2 direction);
Entity *SpawnExplosionFromEntity(Entity *entity);
Rectangle GetEntityRectangle(Entity *entity);

#endif
