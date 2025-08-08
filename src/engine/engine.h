#ifndef Engine_H
#define Engine_H

#include "entitycollection.h"
#include "audio_engine.h"
#include "states/state.h"

#define DEFAULT_BACKGROUND_COLOR RAYWHITE

typedef enum
{
    ENTITY_TEXTURE_PLAYER,
    ENTITY_TEXTURE_REDENEMY,
    ENTITY_TEXTURE_BLUENEMY,
    ENTITY_TEXTURE_EXPLOSION,
    ENTITY_TEXTURE_POWERUP_SPEED,
    ENTITY_TEXTURE_POWERUP_SHOOTING,
    ENTITY_TEXTURE_BULLET,
    // Count
    ENTITY_TEXTURE_COUNT
} ENTITY_TEXTURES;

typedef struct Engine
{
    AudioEngine audio_engine;
    EntityCollection entities;
    Entity *player;
    Texture2D entityTextures[ENTITY_TEXTURE_COUNT];
    GameState game_state;

} Engine;

void InitEngine(Engine *engine);
void HandleInputEngine(Engine *engine);
void UpdateEngine(Engine *engine);
void DrawEngine(Engine *engine);
void FreeEngine(Engine *engine);

#endif
