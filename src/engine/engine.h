#ifndef Engine_H
#define Engine_H

#include "entitycollection.h"
#include "audio_engine.h"
#include "state.h"

#define DEFAULT_BACKGROUND_COLOR RAYWHITE

#define ENEMIES_AMOUNT 5

#define MAX_ENEMY_TEXTURES 5

typedef enum
{
    PLAYER_TEXTURE,
    RED_ENEMY_TEXTURE,
    BLUE_ENEMY_TEXTURE,
    EXPLOSION_TEXTURE,
} ENTITY_TEXTURES;

typedef struct Engine
{
    AudioEngine audio_engine;
    EntityCollection entities;
    Entity *player;
    Texture2D entityTextures[MAX_ENEMY_TEXTURES];
    GameState game_state;

} Engine;

void InitEngine(Engine *engine);
void HandleInputEngine(Engine *engine);
void UpdateEngine(Engine *engine);
void DrawEngine(Engine *engine);
void FreeEngine(Engine *engine);

#endif
