#include "playing.h"
#include "raymath.h"
#include "shared/utils.h"
#include "engine/collision_system.h"
#include "systems/gameplay.h"

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

    if (engine->player->attributes.entitySpecificAttributes.player.shootingCooldown > 0.0f)
    {
        if (IsKeyDown(KEY_D))
            PlayerShootBullet(engine, (Vector2){1, 0});
        if (IsKeyDown(KEY_W))
            PlayerShootBullet(engine, (Vector2){0, -1});
        if (IsKeyDown(KEY_A))
            PlayerShootBullet(engine, (Vector2){-1, 0});
        if (IsKeyDown(KEY_S))
            PlayerShootBullet(engine, (Vector2){0, 1});
    }

    if (IsKeyPressed(KEY_P))
        PauseGame(engine);
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
        case ENTITY_BULLET:
            if (isOffScreen(currEntity))
                currEntity->alive = false;
            break;
        case ENTITY_REDENEMY:
            Vector2 direction = Vector2Normalize(Vector2Subtract(engine->player->position, currEntity->position));
            currEntity->velocity = Vector2Scale(direction, currEntity->attributes.speed);
            break;
        case ENTITY_EXPLOSION:
            currEntity->attributes.entitySpecificAttributes.explosion.lifetime -= GetFrameTime();
            if (currEntity->attributes.entitySpecificAttributes.explosion.lifetime < 0.0f)
                currEntity->alive = false;
            break;
        case ENTITY_POWERUP_SPEED:
            break;
        case ENTITY_PLAYER:
            float *powerupSpeedLifetime = &currEntity->attributes.entitySpecificAttributes.player.powerupSpeedLifetime;
            float *powerupShootingLifetime = &currEntity->attributes.entitySpecificAttributes.player.powerupShootingLifetime;
            float *shootingRemainingCooldown = &currEntity->attributes.entitySpecificAttributes.player.shootingRemainingCooldown;
            if (*powerupSpeedLifetime > 0.0f)
            {
                *powerupSpeedLifetime -= GetFrameTime();
            }
            else
            {
                *powerupSpeedLifetime = 0.0f;
                currEntity->attributes.speed = DEFAULT_PLAYER_SPEED;
            }
            if (*powerupShootingLifetime > 0.0f)
            {
                *powerupShootingLifetime -= GetFrameTime();
            }
            else
            {
                *powerupShootingLifetime = 0.0f;
                currEntity->attributes.entitySpecificAttributes.player.shootingCooldown = DEFAULT_PLAYER_SHOOTING_COOLDOWN;
            }
            if (*shootingRemainingCooldown > 0.0f)
            {
                *shootingRemainingCooldown -= GetFrameTime();
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
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);

    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};
    const char *waveText = TextFormat("WAVE %02i", engine->waveSystem.currentWave);
    const int waveTextFontSize = 50;
    int waveTextWidth = MeasureText(waveText, waveTextFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){waveTextWidth, waveTextFontSize});

    DrawText(waveText, textPosition.x, textPosition.y, waveTextFontSize, GRAY);
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;
        Vector2 position = FromCenteredReturnTopLeftPosition(currEntity);

        switch (currEntity->type)
        {
        case ENTITY_PLAYER:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_PLAYER], position, WHITE);
            break;
        case ENTITY_REDENEMY:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_REDENEMY], position, WHITE);
            break;
        case ENTITY_BLUEENEMY:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_BLUENEMY], position, WHITE);
            break;
        case ENTITY_BULLET:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_BULLET], position, WHITE);
            break;
        case ENTITY_EXPLOSION:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_EXPLOSION], position, WHITE);
            break;
        case ENTITY_POWERUP_SHOOTING:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_POWERUP_SHOOTING], position, WHITE);
            break;
        case ENTITY_POWERUP_SPEED:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_POWERUP_SPEED], position, WHITE);
            break;
        }
    }
}
