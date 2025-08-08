#include "entity.h"
#include "raymath.h"
#include "stdlib.h"

Entity *DefaultPlayer()
{
    Entity *player = malloc(sizeof(Entity));
    player->position = Vector2Zero();
    player->velocity = Vector2Zero();
    player->type = ENTITY_PLAYER;
    player->attributes.speed = DEFAULT_PLAYER_SPEED;
    player->attributes.color = WHITE;
    player->attributes.size = (Vector2){DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT};
    player->attributes.entitySpecificAttributes.player.powerupSpeedLifetime = 0.0f;
    player->attributes.entitySpecificAttributes.player.powerupShootingLifetime = 0.0f;
    player->attributes.entitySpecificAttributes.player.shootingCooldown = DEFAULT_PLAYER_SHOOTING_COOLDOWN;
    player->attributes.entitySpecificAttributes.player.shootingRemainingCooldown = 0.0f;
    player->alive = true;
}
Entity *DefaultRedEnemy()
{
    Entity *enemy = malloc(sizeof(Entity));
    enemy->position = Vector2Zero();
    enemy->velocity = Vector2Zero();
    enemy->type = ENTITY_REDENEMY;
    enemy->attributes.speed = DEFAULT_ENEMY_SPEED;
    enemy->attributes.color = WHITE;
    enemy->attributes.size = (Vector2){DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT};
    enemy->alive = true;
    enemy->attributes.entitySpecificAttributes.waveEntity.wave = NULL;
}
Entity *DefaultBlueEnemy()
{
    Entity *enemy = malloc(sizeof(Entity));
    enemy->position = Vector2Zero();
    enemy->velocity = Vector2Zero();
    enemy->type = ENTITY_BLUEENEMY;
    enemy->attributes.speed = DEFAULT_ENEMY_SPEED;
    enemy->attributes.color = WHITE;
    enemy->attributes.size = (Vector2){DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT};
    enemy->alive = true;
    enemy->attributes.entitySpecificAttributes.waveEntity.wave = NULL;
}

Entity *DefaultPowerupSpeed()
{
    Entity *powerUp = malloc(sizeof(Entity));
    powerUp->position = Vector2Zero();
    powerUp->velocity = Vector2Zero();
    powerUp->type = ENTITY_POWERUP_SPEED;
    powerUp->attributes.speed = 0.0f;
    powerUp->attributes.color = WHITE;
    powerUp->attributes.size = (Vector2){DEFAULT_POWERUP_WIDTH, DEFAULT_POWERUP_HEIGHT};
    powerUp->alive = true;
    powerUp->attributes.entitySpecificAttributes.waveEntity.wave = NULL;
}
Entity *DefaultPowerupShooting()
{
    Entity *powerUp = malloc(sizeof(Entity));
    powerUp->position = Vector2Zero();
    powerUp->velocity = Vector2Zero();
    powerUp->type = ENTITY_POWERUP_SHOOTING;
    powerUp->attributes.speed = 0.0f;
    powerUp->attributes.color = WHITE;
    powerUp->attributes.size = (Vector2){DEFAULT_POWERUP_WIDTH, DEFAULT_POWERUP_HEIGHT};
    powerUp->alive = true;
    powerUp->attributes.entitySpecificAttributes.waveEntity.wave = NULL;
}

Entity *DefaultBulletFromEntity(Entity *entity, Vector2 direction)
{
    Entity *bullet = malloc(sizeof(Entity));
    bullet->type = ENTITY_BULLET;
    bullet->position = entity->position;
    bullet->velocity = Vector2Scale(direction, DEFAULT_BULLET_SPEED);
    bullet->attributes.color = DEFAULT_BULLET_COLOR;
    bullet->attributes.size = (Vector2){DEFAULT_BULLET_WIDTH, DEFAULT_BULLET_HEIGHT};
    bullet->attributes.speed = DEFAULT_BULLET_SPEED;
    bullet->alive = true;
    bullet->attributes.entitySpecificAttributes.bullet.shotFrom = entity;
}

Rectangle GetEntityRectangle(Entity *entity)

{
    return (Rectangle){
        entity->position.x - entity->attributes.size.x / 2.0f,
        entity->position.y - entity->attributes.size.y / 2.0f,
        entity->attributes.size.x,
        entity->attributes.size.y};
}

Entity *SpawnExplosionFromEntity(Entity *entity)
{
    Entity *explosion = malloc(sizeof(Entity));
    explosion->type = ENTITY_EXPLOSION;
    explosion->position = entity->position;
    explosion->velocity = Vector2Zero();
    explosion->attributes.size = (Vector2){DEFAULT_EXPLOSION_WIDTH, DEFAULT_EXPLOSION_HEIGHT};
    explosion->attributes.speed = 0.0f;
    explosion->attributes.color = WHITE;
    explosion->attributes.entitySpecificAttributes.explosion.lifetime = 1.0f;
    explosion->alive = true;
}
