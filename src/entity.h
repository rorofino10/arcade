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
#define DEFAULT_BULLET_WIDTH 11
#define DEFAULT_BULLET_HEIGHT 5
#define DEFAULT_BULLET_COLOR BLACK

#define DEFAULT_EXPLOSION_WIDTH 50
#define DEFAULT_EXPLOSION_HEIGHT 50

#define DEFAULT_POWERUP_WIDTH 50
#define DEFAULT_POWERUP_HEIGHT 50

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
    ENTITY_BULLET,
    ENTITY_REDENEMY,
    ENTITY_BLUENEMY,
    ENTITY_PLAYER,
    ENTITY_EXPLOSION,
    ENTITY_POWERUP,

    // To see how many entities
    ENTITY_TYPE_COUNT
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
    struct Entity *shotFrom;
} BulletAttributes;

typedef struct
{
    float speed;
    Vector2 size;
    Color color;
    union
    {
        ExplosionAttributes explosion;
        PlayerAttributes player;
        BulletAttributes bullet;

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
