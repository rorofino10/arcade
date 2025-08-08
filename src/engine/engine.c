#include "engine.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

#include "states/playing.h"
#include "states/title_screen.h"
#include "states/paused_screen.h"
#include "states/lost_screen.h"

#include "collision_system.h"
#include "systems/gameplay.h"
const int POWER_UP_AMOUNT = 1;

void InitEngine(Engine *engine)
{
    engine->game_state = STATE_TITLE_SCREEN;

    InitEntityCollection(&engine->entities);

    SpawnPlayer(engine, (Vector2){0, 0});

    Image playerImage = LoadImage("assets/player_character.png");
    ImageResize(&playerImage, engine->player->attributes.size.x, engine->player->attributes.size.y);
    engine->entityTextures[ENTITY_TEXTURE_PLAYER] = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);

    Image enemyRedImage = LoadImage("assets/red_enemy.png");
    ImageResize(&enemyRedImage, DEFAULT_ENEMY_WIDTH, DEFAULT_ENEMY_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_REDENEMY] = LoadTextureFromImage(enemyRedImage);
    UnloadImage(enemyRedImage);

    Image enemyBlueImage = LoadImage("assets/blue_enemy.png");
    ImageResize(&enemyBlueImage, DEFAULT_ENEMY_WIDTH, DEFAULT_ENEMY_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_BLUENEMY] = LoadTextureFromImage(enemyBlueImage);
    UnloadImage(enemyBlueImage);

    Image explosionImage = LoadImage("assets/explosion.png");
    ImageResize(&explosionImage, DEFAULT_EXPLOSION_WIDTH, DEFAULT_EXPLOSION_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_EXPLOSION] = LoadTextureFromImage(explosionImage);
    UnloadImage(explosionImage);

    Image powerupImage = LoadImage("assets/powerup.png");
    ImageResize(&powerupImage, DEFAULT_POWERUP_WIDTH, DEFAULT_POWERUP_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_POWERUP] = LoadTextureFromImage(powerupImage);
    // engine->entityTextures[ENTITY_TEXTURE_BULLET] = LoadTextureFromImage(powerupImage);
    UnloadImage(powerupImage);

    Image bulletImage = LoadImage("assets/bullet.png");
    ImageResize(&bulletImage, DEFAULT_BULLET_WIDTH, DEFAULT_BULLET_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_BULLET] = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    srand(time(NULL));

    for (int i = 0; i < ENEMIES_AMOUNT; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnRedEnemy(engine, position);
    }
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnPowerup(engine, position);
    }

    InitAudioEngine(&engine->audio_engine);
    InitCollisionSystem();
    InitGameplaySystem();
}

void HandleInputEngine(Engine *engine)
{
    switch (engine->game_state)
    {
    case STATE_PLAYING:
        HandleInputPlaying(engine);
        break;
    case STATE_TITLE_SCREEN:
        HandleInputTitleScreen(engine);
        break;
    case STATE_PAUSED:
        HandleInputPausedScreen(engine);
        break;
    case STATE_LOST:
        HandleInputLostScreen(engine);
        break;
    default:
        break;
    }
}

void UpdateEngine(Engine *engine)
{
    switch (engine->game_state)
    {
    case STATE_PLAYING:
        UpdatePlaying(engine);
        break;
    case STATE_TITLE_SCREEN:
        UpdateTitleScreen(engine);
        break;
    case STATE_PAUSED:
        UpdatePausedScreen(engine);
        break;
    case STATE_LOST:
        UpdateLostScreen(engine);
        break;
    default:
        break;
    }

    UpdateAudioEngine(&engine->audio_engine);
}

void DrawEngine(Engine *engine)
{

    BeginDrawing();
    ClearBackground(DEFAULT_BACKGROUND_COLOR);

    switch (engine->game_state)
    {
    case STATE_PLAYING:
        DrawPlaying(engine);
        break;
    case STATE_TITLE_SCREEN:
        DrawTitleScreen(engine);
        break;
    case STATE_PAUSED:
        DrawPausedScreen(engine);
        break;
    case STATE_LOST:
        DrawLostScreen(engine);
        break;
    default:
        break;
    }

    EndDrawing();
}

void FreeEngine(Engine *engine)
{
    FreeEntityCollection(&engine->entities);

    for (int i = 0; i < ENTITY_TEXTURE_COUNT; i++)
    {
        UnloadTexture(engine->entityTextures[i]);
    }

    FreeAudioEngine(&engine->audio_engine);

    CloseWindow();
}
