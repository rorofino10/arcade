#include "engine.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

const int POWER_UP_AMOUNT = 1;

void InitEngine(Engine *engine)
{
    engine->player = DefaultPlayer();
    InitEntityCollection(&engine->entities);
    AppendEntityCollection(&engine->entities, engine->player);

    Image playerImage = LoadImage("assets/player_character.png");
    ImageResize(&playerImage, engine->player->attributes.size.x, engine->player->attributes.size.y);
    engine->entityTextures[PLAYER_TEXTURE] = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);

    Image enemyRedImage = LoadImage("assets/red_enemy.png");
    ImageResize(&enemyRedImage, DEFAULT_ENEMY_WIDTH, DEFAULT_ENEMY_HEIGHT);
    engine->entityTextures[RED_ENEMY_TEXTURE] = LoadTextureFromImage(enemyRedImage);
    UnloadImage(enemyRedImage);

    Image enemyBlueImage = LoadImage("assets/blue_enemy.png");
    ImageResize(&enemyBlueImage, DEFAULT_ENEMY_WIDTH, DEFAULT_ENEMY_HEIGHT);
    engine->entityTextures[BLUE_ENEMY_TEXTURE] = LoadTextureFromImage(enemyBlueImage);
    UnloadImage(enemyBlueImage);

    Image explosionImage = LoadImage("assets/explosion.png");
    ImageResize(&explosionImage, DEFAULT_EXPLOSION_WIDTH, DEFAULT_EXPLOSION_HEIGHT);
    engine->entityTextures[EXPLOSION_TEXTURE] = LoadTextureFromImage(explosionImage);
    UnloadImage(explosionImage);

    srand(time(NULL));

    for (int i = 0; i < ENEMIES_AMOUNT; i++)
    {
        Entity *enemy = DefaultEnemy();
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        enemy->position = (Vector2){randX, randY};
        AppendEntityCollection(&engine->entities, enemy);
    }
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        Entity *powerUp = DefaultPowerUp();
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        powerUp->position = (Vector2){randX, randY};
        AppendEntityCollection(&engine->entities, powerUp);
    }

    InitAudioEngine(&engine->audio_engine);
}

void ShootBullet(Engine *engine, Entity *entity, Vector2 direction)
{
    Entity *bullet = DefaultBulletFromEntity(entity, direction);
    AppendEntityCollection(&engine->entities, bullet);
    PlaySoundAudioEngine(&engine->audio_engine, BULLET_SOUND);
}

void HandleInputEngine(Engine *engine)
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

void UpdateEngine(Engine *engine)
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

    UpdateAudioEngine(&engine->audio_engine);
}

Vector2 centeredPosition(Entity *entity)
{
    (Vector2){entity->position.x - entity->attributes.size.x / 2, entity->position.y - entity->attributes.size.y / 2};
}

Vector2 FromCenteredReturnTopLeftPosition(Entity *entity)
{
    Vector2 center = entity->position;
    Vector2 size = entity->attributes.size;
    return (Vector2){
        center.x - size.x / 2.0f,
        center.y - size.y / 2.0f};
}

void DrawEngine(Engine *engine)
{

    BeginDrawing();
    ClearBackground(DEFAULT_BACKGROUND_COLOR);

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

    EndDrawing();
}

void FreeEngine(Engine *engine)
{
    FreeEntityCollection(&engine->entities);

    for (int i = 0; i < MAX_ENEMY_TEXTURES; i++)
    {
        UnloadTexture(engine->entityTextures[i]);
    }

    FreeAudioEngine(&engine->audio_engine);

    CloseWindow();
}
