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
#include "states/win_screen.h"

#include "collision_system.h"
#include "systems/gameplay.h"
const int POWER_UP_AMOUNT = 5;
const int ENEMIES_AMOUNT = 0;

void InitEngine(Engine *engine)
{
    engine->game_state = STATE_TITLE_SCREEN;

    Image playerImage = LoadImage("assets/player_character.png");
    ImageResize(&playerImage, DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT);
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
    engine->entityTextures[ENTITY_TEXTURE_POWERUP_SPEED] = LoadTextureFromImage(powerupImage);
    UnloadImage(powerupImage);

    Image powerupShootingImage = LoadImage("assets/powerup_shooting.png");
    ImageResize(&powerupShootingImage, DEFAULT_POWERUP_WIDTH, DEFAULT_POWERUP_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_POWERUP_SHOOTING] = LoadTextureFromImage(powerupShootingImage);
    UnloadImage(powerupShootingImage);

    Image bulletImage = LoadImage("assets/bullet.png");
    ImageResize(&bulletImage, DEFAULT_BULLET_WIDTH, DEFAULT_BULLET_HEIGHT);
    engine->entityTextures[ENTITY_TEXTURE_BULLET] = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    InitWaveSystem(&engine->waveSystem);
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
    case STATE_WIN:
        HandleInputWinScreen(engine);
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
    case STATE_WIN:
        UpdateWinScreen(engine);
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
    case STATE_WIN:
        DrawWinScreen(engine);
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
