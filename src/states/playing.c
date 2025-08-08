#include "playing.h"
#include "raymath.h"
#include "shared/utils.h"
#include "engine/collision_system.h"

void KillEntity(Engine *engine, Entity *entity)
{
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_EXPLOSION);
    Entity *explosion = SpawnExplosionFromEntity(entity);
    AppendEntityCollection(&engine->entities, explosion);
    entity->alive = false;
}

void ShootBullet(Engine *engine, Entity *entity, Vector2 direction)
{
    Entity *bullet = DefaultBulletFromEntity(entity, direction);
    AppendEntityCollection(&engine->entities, bullet);
    PlaySoundAudioEngine(&engine->audio_engine, SOUND_EFFECT_BULLET);
}

void HandleInputPlaying(Engine *engine)
{
    Vector2 velocity = {0};

    if (IsKeyDown(KEY_RIGHT))
        velocity.x += 1;
    if (IsKeyDown(KEY_LEFT))
        velocity.x -= 1;
    if (IsKeyDown(KEY_DOWN))
        velocity.y += 1;
    if (IsKeyDown(KEY_UP))
        velocity.y -= 1;

    float speed = engine->player->attributes.speed;
    engine->player->velocity = Vector2Scale(velocity, speed);

    if (IsKeyPressed(KEY_D))
        ShootBullet(engine, engine->player, (Vector2){1, 0});
    if (IsKeyPressed(KEY_W))
        ShootBullet(engine, engine->player, (Vector2){0, -1});
    if (IsKeyPressed(KEY_A))
        ShootBullet(engine, engine->player, (Vector2){-1, 0});
    if (IsKeyPressed(KEY_S))
        ShootBullet(engine, engine->player, (Vector2){0, 1});

    if (IsKeyPressed(KEY_P))
        engine->game_state = STATE_PAUSED;
}

bool isOffScreen(Entity *entity)
{
    return entity->position.x < 0 || entity->position.y < 0 || entity->position.x > GetScreenWidth() || entity->position.y > GetScreenHeight();
}

void UpdatePlaying(Engine *engine)
{
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;

        currEntity->position = Vector2Add(currEntity->position, Vector2Scale(currEntity->velocity, GetFrameTime()));
        switch (currEntity->type)
        {
        case BULLET:
            if (isOffScreen(currEntity))
                currEntity->alive = false;
            break;
        case RED_ENEMY:
            Vector2 direction = Vector2Normalize(Vector2Subtract(engine->player->position, currEntity->position));
            currEntity->velocity = Vector2Scale(direction, currEntity->attributes.speed);
            break;
        case EXPLOSION:
            currEntity->attributes.entitySpecificAttributes.explosion.lifetime -= GetFrameTime();
            if (currEntity->attributes.entitySpecificAttributes.explosion.lifetime < 0.0f)
                currEntity->alive = false;
            break;
        case POWER_UP:
            break;
        case PLAYER_CONTROLLED:
            float *powerUpLifetime = &currEntity->attributes.entitySpecificAttributes.player.powerUpLifetime;
            if (*powerUpLifetime > 0.0f)
            {
                *powerUpLifetime -= GetFrameTime();
            }
            else
            {
                *powerUpLifetime = 0.0f;
                currEntity->attributes.speed = DEFAULT_PLAYER_SPEED;
            }
            break;
        default:
            break;
        }
    }
    UpdateCollisions(engine);
    FreeDeadEntitiesFromCollection(&engine->entities);
}

void DrawPlaying(Engine *engine)
{
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;
        Vector2 position = FromCenteredReturnTopLeftPosition(currEntity);
        switch (currEntity->type)
        {
        case PLAYER_CONTROLLED:
            DrawTextureV(engine->entityTextures[PLAYER_TEXTURE], position, WHITE);
            break;
        case RED_ENEMY:
            DrawTextureV(engine->entityTextures[RED_ENEMY_TEXTURE], position, WHITE);
            break;
        case BLUE_ENEMY:
            DrawTextureV(engine->entityTextures[BLUE_ENEMY_TEXTURE], position, WHITE);
            break;
        case BULLET:
            DrawCircleV(position, currEntity->attributes.size.x, DEFAULT_BULLET_COLOR);
            break;
        case EXPLOSION:
            DrawTextureV(engine->entityTextures[EXPLOSION_TEXTURE], position, WHITE);
            break;
        case POWER_UP:
            DrawTextureV(engine->entityTextures[BLUE_ENEMY_TEXTURE], position, WHITE);
            break;
        }
    }
}
