#include "playing.h"
#include "raymath.h"
#include "shared/utils.h"

void ShootBullet(Engine *engine, Entity *entity, Vector2 direction)
{
    Entity *bullet = DefaultBulletFromEntity(entity, direction);
    AppendEntityCollection(&engine->entities, bullet);
    PlaySoundAudioEngine(&engine->audio_engine, BULLET_SOUND);
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

bool CheckCollisionBetweenEntities(Entity *a, Entity *b)
{
    return CheckCollisionRecs(GetEntityRectangle(a), GetEntityRectangle(b));
}

CollectionNode *checkCollision(Engine *engine, CollectionNode *entityNode)
{
    Entity *a = entityNode->entity;
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *b = curr->entity;
        if (a == b || b->type == PLAYER_CONTROLLED)
            continue;
        bool areColliding = CheckCollisionBetweenEntities(a, b);
        if (areColliding)
            return curr;
    }
    return NULL;
}

void KillEnemy(Engine *engine, Entity *enemy)
{
    PlaySoundAudioEngine(&engine->audio_engine, EXPLOSION_SOUND);
    Entity *explosion = SpawnExplosionFromEntity(enemy);
    AppendEntityCollection(&engine->entities, explosion);
    enemy->alive = false;
}

void UpdatePlaying(Engine *engine)
{
    CollectionNode *curr = engine->entities.head;
    // for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    while (curr != NULL)
    {
        Entity *currEntity = curr->entity;
        if (!currEntity->alive)
        {

            CollectionNode *toDelete = curr;
            curr = curr->next;
            FreeEntityFromEntityCollection(&engine->entities, toDelete);
            continue;
        }
        currEntity->position = Vector2Add(currEntity->position, Vector2Scale(currEntity->velocity, GetFrameTime()));
        switch (currEntity->type)
        {
        case BULLET:
            if (isOffScreen(currEntity))
            {
                currEntity->alive = false;
            }
            CollectionNode *collidedNode = checkCollision(engine, curr);
            if (collidedNode != NULL)
            {
                currEntity->alive = false;
                KillEnemy(engine, collidedNode->entity);
            }
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
            if (CheckCollisionBetweenEntities(engine->player, currEntity))
            {
                engine->player->attributes.speed *= 2.0f;
                engine->player->attributes.entitySpecificAttributes.player.powerUpLifetime = POWER_UP_LIFETIME;
                currEntity->alive = false;
            }
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
        curr = curr->next;
    }
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
