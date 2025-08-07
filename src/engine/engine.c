#include "engine.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

#include "states/playing.h"
#include "states/title_screen.h"
#include "states/paused_screen.h"

#include "collision_system.h"

const int POWER_UP_AMOUNT = 1;

void InitEngine(Engine *engine)
{
    engine->game_state = STATE_TITLE_SCREEN;

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
    InitCollisionSystem();
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
    default:
        break;
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
