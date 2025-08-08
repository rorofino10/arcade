#include "gameplay.h"
#include "entity.h"
#include "raymath.h"

DeathHandler deathHandlers[ENTITY_TYPE_COUNT];

void SpawnPlayer(Engine *engine, Vector2 position)
{
    engine->player = DefaultPlayer();
    AppendEntityCollection(&engine->entities, engine->player);
}

void SpawnRedEnemy(Engine *engine, Vector2 position)
{
    Entity *enemy = DefaultRedEnemy();
    enemy->position = position;
    AppendEntityCollection(&engine->entities, enemy);
}

void SpawnBlueEnemy(Engine *engine, Vector2 position)
{
    Entity *enemy = DefaultBlueEnemy();
    enemy->position = position;
    AppendEntityCollection(&engine->entities, enemy);
}

void handleBlueEnemyDeath(Engine *engine, Entity *entity)
{
    const float fullCircle = 360;
    const float amount = 10;
    for (float deg = 0; deg < fullCircle; deg += fullCircle / amount)
    {
        float rad = deg * DEG2RAD;
        Vector2 dir = (Vector2){cosf(rad), sinf(rad)};
        ShootBullet(engine, entity, dir);
    }
}
void handlePlayerDeath(Engine *engine, Entity *entity)
{
    LoseGame(engine);
}

void handleEntityDeath(Engine *engine, Entity *entity)
{
    DeathHandler handler = deathHandlers[entity->type];
    if (handler)
    {
        handler(engine, entity);
    }
}

void KillEntity(Engine *engine, Entity *entity)
{
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_EXPLOSION);
    Entity *explosion = SpawnExplosionFromEntity(entity);
    AppendEntityCollection(&engine->entities, explosion);
    entity->alive = false;

    handleEntityDeath(engine, entity);
}

void SpawnPowerupSpeed(Engine *engine, Vector2 position)
{
    Entity *powerUp = DefaultPowerupSpeed();
    powerUp->position = position;
    AppendEntityCollection(&engine->entities, powerUp);
}
void SpawnPowerupShooting(Engine *engine, Vector2 position)
{
    Entity *powerUp = DefaultPowerupShooting();
    powerUp->position = position;
    AppendEntityCollection(&engine->entities, powerUp);
}

void ShootBullet(Engine *engine, Entity *entity, Vector2 direction)
{
    Entity *bullet = DefaultBulletFromEntity(entity, direction);
    AppendEntityCollection(&engine->entities, bullet);
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_BULLET);
}

void PlayerShootBullet(Engine *engine, Vector2 direction)
{
    float *shootingRemainingCooldown = &engine->player->attributes.entitySpecificAttributes.player.shootingRemainingCooldown;
    float *shootingCooldown = &engine->player->attributes.entitySpecificAttributes.player.shootingCooldown;
    bool canShoot = !(*shootingRemainingCooldown > 0.0f);
    if (canShoot)
    {
        ShootBullet(engine, engine->player, direction);
        *shootingRemainingCooldown = *shootingCooldown;
    }
}

void InitGameplaySystem()
{
    for (int i = 0; i < ENTITY_TYPE_COUNT; i++)
    {
        deathHandlers[i] = NULL;
    }

    deathHandlers[ENTITY_BLUENEMY] = handleBlueEnemyDeath;
    deathHandlers[ENTITY_PLAYER] = handlePlayerDeath;
}
