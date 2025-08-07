#ifndef PLAYING_H
#define PLAYING_H

#include "engine/engine.h"

void HandleInputPlaying(Engine *engine);
void UpdatePlaying(Engine *engine);
void DrawPlaying(Engine *engine);
void KillEntity(Engine *engine, Entity *entity);
#endif
