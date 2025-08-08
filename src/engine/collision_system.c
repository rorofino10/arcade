#include "collision_system.h"
#include "states/playing.h"

CollisionHandler collisionHandlers[ENTITY_TYPE_COUNT][ENTITY_TYPE_COUNT];

void handlePlayerEnemy(Engine *engine, Entity *player, Entity *enemy)
{
    KillEntity(engine, player);
}

void handleBulletEntity(Engine *engine, Entity *bullet, Entity *entity)
{
    if (bullet->attributes.entitySpecificAttributes.bullet.shotFrom->type == entity->type)
        return;
    bullet->alive = false;
    KillEntity(engine, entity);
}

void ApplyPowerupSpeed(Engine *engine, Entity *player)
{
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_POWERUP);
    player->attributes.speed *= 2.0f;
    player->attributes.entitySpecificAttributes.player.powerupSpeedLifetime = DEFAULT_POWERUP_SPEED_LIFETIME;
}

void handlePlayerPowerupSpeed(Engine *engine, Entity *player, Entity *powerup)
{
    ApplyPowerupSpeed(engine, player);
    powerup->alive = false;
}
void ApplyPowerupShooting(Engine *engine, Entity *player)
{
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_POWERUP);
    player->attributes.entitySpecificAttributes.player.powerupShootingLifetime = DEFAULT_POWERUP_SHOOTING_LIFETIME;
    player->attributes.entitySpecificAttributes.player.shootingCooldown = DEFAULT_POWERUP_SHOOTING_COOLDOWN;
    player->attributes.entitySpecificAttributes.player.shootingRemainingCooldown = 0.0f;
}

void handlePlayerPowerupShooting(Engine *engine, Entity *player, Entity *powerup)
{
    ApplyPowerupShooting(engine, player);
    powerup->alive = false;
}

void InitCollisionSystem()
{
    for (int i = 0; i < ENTITY_TYPE_COUNT; ++i)
        for (int j = 0; j < ENTITY_TYPE_COUNT; ++j)
            collisionHandlers[i][j] = NULL;

    collisionHandlers[ENTITY_BULLET][ENTITY_REDENEMY] = handleBulletEntity;
    collisionHandlers[ENTITY_BULLET][ENTITY_BLUEENEMY] = handleBulletEntity;
    collisionHandlers[ENTITY_BULLET][ENTITY_PLAYER] = handleBulletEntity;
    collisionHandlers[ENTITY_PLAYER][ENTITY_REDENEMY] = handlePlayerEnemy;
    collisionHandlers[ENTITY_PLAYER][ENTITY_POWERUP_SPEED] = handlePlayerPowerupSpeed;
    collisionHandlers[ENTITY_PLAYER][ENTITY_POWERUP_SHOOTING] = handlePlayerPowerupShooting;
}

bool CheckCollisionBetweenEntities(Entity *a, Entity *b)
{
    return CheckCollisionRecs(GetEntityRectangle(a), GetEntityRectangle(b));
}

void HandleCollisionBetweenEntities(Engine *engine, Entity *a, Entity *b)
{

    CollisionHandler handler = collisionHandlers[a->type][b->type];
    if (handler)
    {
        handler(engine, a, b);
    }
    else
    {
        handler = collisionHandlers[b->type][a->type];
        if (handler)
        {
            handler(engine, b, a);
        }
    }
}

void UpdateCollisions(Engine *engine)
{
    for (CollectionNode *currA = engine->entities.head; currA != NULL; currA = currA->next)
    {
        Entity *entityA = currA->entity;

        for (CollectionNode *currB = currA->next; currB != NULL; currB = currB->next)
        {
            Entity *entityB = currB->entity;

            if (CheckCollisionBetweenEntities(entityA, entityB))
            {
                HandleCollisionBetweenEntities(engine, entityA, entityB);
            }
        }
    }
}
