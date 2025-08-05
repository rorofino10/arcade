#include "engine.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

void InitEngine(Engine *engine)
{
    engine->playerTexture = LoadTexture("assets/player_character.png");
    srand(time(NULL));

    engine->player = malloc(sizeof(Entity));
    engine->player->position = Vector2Zero();
    engine->player->velocity = Vector2Zero();
    engine->player->type = PLAYER_CONTROLLED;

    InitEntityCollection(&engine->entities);
    AppendEntityCollection(&engine->entities, engine->player);

    for (int i = 0; i < ENEMIES_AMMOUNT; i++)
    {
        Entity *enemy = malloc(sizeof(Entity));
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        *enemy = (Entity){.position = (Vector2){randX, randY}, .velocity = Vector2Zero(), .type = ENEMY};
        AppendEntityCollection(&engine->entities, enemy);
    }
}

void ShootBullet(Engine *engine, Entity *entity, Vector2 direction)
{
    Entity *bullet = malloc(sizeof(Entity));
    bullet->type = BULLET;
    bullet->position = entity->position;
    bullet->velocity = Vector2Scale(direction, BULLET_SPEED);
    AppendEntityCollection(&engine->entities, bullet);
}

void HandleInputEngine(Engine *engine)
{
    if (IsKeyDown(KEY_RIGHT))
        engine->player->velocity.x = PLAYER_SPEED;
    else if (IsKeyDown(KEY_LEFT))
        engine->player->velocity.x = -1 * PLAYER_SPEED;
    else
        engine->player->velocity.x = 0;
    if (IsKeyDown(KEY_UP))
        engine->player->velocity.y = -1 * PLAYER_SPEED;
    else if (IsKeyDown(KEY_DOWN))
        engine->player->velocity.y = PLAYER_SPEED;
    else
        engine->player->velocity.y = 0;

    if (IsKeyDown(KEY_RIGHT))
        engine->player->velocity.x = PLAYER_SPEED;
    else if (IsKeyDown(KEY_LEFT))
        engine->player->velocity.x = -1 * PLAYER_SPEED;
    else
        engine->player->velocity.x = 0;
    if (IsKeyDown(KEY_UP))
        engine->player->velocity.y = -1 * PLAYER_SPEED;
    else if (IsKeyDown(KEY_DOWN))
        engine->player->velocity.y = PLAYER_SPEED;
    else
        engine->player->velocity.y = 0;

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

void UpdateEngine(Engine *engine)
{
    CollectionNode *curr = engine->entities.head;
    CollectionNode *prev = NULL;
    while (curr != NULL)
    {
        Entity *currEntity = curr->entity;
        currEntity->position = Vector2Add(currEntity->position, Vector2Scale(currEntity->velocity, GetFrameTime()));
        if (currEntity->type == BULLET && isOffScreen(currEntity))
        {
            CollectionNode *toDeleteBullet = curr;
            if (prev == NULL)
            {
                engine->entities.head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            curr = curr->next;
            free(toDeleteBullet->entity);
            free(toDeleteBullet);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

void DrawEngine(Engine *engine)
{
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;
        switch (currEntity->type)
        {
        case PLAYER_CONTROLLED:
            DrawRectangleV(currEntity->position, (Vector2){50, 50}, RED);
            break;
        case ENEMY:
            DrawRectangleV(currEntity->position, (Vector2){50, 50}, BLUE);
            break;
        case BULLET:
            DrawCircleV(currEntity->position, 5, BLACK);
            break;
        }
    }
}

void FreeEngine(Engine *engine)
{
    FreeEntityCollection(&engine->entities);
    UnloadTexture(engine->playerTexture);
    UnloadTexture(engine->bulletTexture);
    UnloadTexture(engine->enemyTexture);

    CloseAudioDevice();
    CloseWindow();
}
