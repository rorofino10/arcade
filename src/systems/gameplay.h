#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "engine/engine.h"

typedef void (*DeathHandler)(Engine *engine, Entity *entity);

void SpawnPlayer(Engine *engine, Vector2 position);
void SpawnBlueEnemy(Engine *engine, Vector2 position);
void SpawnRedEnemy(Engine *engine, Vector2 position);
void SpawnPowerupSpeed(Engine *engine, Vector2 position);
void SpawnPowerupShooting(Engine *engine, Vector2 position);

void PlayerShootBullet(Engine *engine, Vector2 direction);
void ShootBullet(Engine *engine, Entity *from, Vector2 direction);
void KillEntity(Engine *engine, Entity *entity);

void InitGameplaySystem();

#endif
