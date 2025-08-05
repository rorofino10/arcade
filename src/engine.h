#ifndef Engine_H
#define Engine_H

#include "entitycollection.h"

#define ENEMIES_AMMOUNT 5
typedef struct
{
    EntityCollection entities;
    Entity *player;
    Texture2D playerTexture;
    Texture2D bulletTexture;
    Texture2D enemyTexture;

} Engine;

void InitEngine(Engine *engine);
void HandleInputEngine(Engine *engine);
void UpdateEngine(Engine *engine);
void DrawEngine(Engine *engine);
void FreeEngine(Engine *engine);

#endif
