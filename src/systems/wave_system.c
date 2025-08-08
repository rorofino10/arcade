#include "wave_system.h"
#include "gameplay.h"
#include "engine/engine.h"
#include "states/state.h"

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

GameWave waves[WAVES_AMOUNT] = {
    {
        .redEnemiesAmount = 1,
        .blueEnemiesAmount = 0,
        .powerupShootingAmount = 2,
        .powerupSpeedAmount = 3,
        .stats = {0, 0, 0, 0},
        .remainingTime = 5.0f,
    },
    {
        .redEnemiesAmount = 3,
        .blueEnemiesAmount = 2,
        .powerupShootingAmount = 2,
        .powerupSpeedAmount = 3,
        .stats = {0, 0, 0, 0},
        .remainingTime = 5.0f,
    },
    {
        .redEnemiesAmount = 3,
        .blueEnemiesAmount = 2,
        .powerupShootingAmount = 2,
        .powerupSpeedAmount = 3,
        .stats = {0, 0, 0, 0},
        .remainingTime = 5.0f,
    },
};

void InitWaveSystem(WaveSystem *waveSystem)
{
    waveSystem->currentWave = 0;

    for (int i = 0; i < WAVES_AMOUNT; i++)
    {
        waveSystem->waves[i].redEnemiesAmount = waves[i].redEnemiesAmount;
        waveSystem->waves[i].blueEnemiesAmount = waves[i].blueEnemiesAmount;
        waveSystem->waves[i].powerupShootingAmount = waves[i].powerupShootingAmount;
        waveSystem->waves[i].powerupSpeedAmount = waves[i].powerupSpeedAmount;
    }
}

void SpawnWaveEntity(Engine *engine, Vector2 position, EntityType type, Wave *wave)
{
    Entity *entity;
    switch (type)
    {
    case ENTITY_REDENEMY:
        entity = SpawnRedEnemy(engine, position);
        break;
    case ENTITY_BLUEENEMY:
        entity = SpawnBlueEnemy(engine, position);
        break;
    case ENTITY_POWERUP_SHOOTING:
        entity = SpawnPowerupShooting(engine, position);
        break;
    case ENTITY_POWERUP_SPEED:
        entity = SpawnPowerupSpeed(engine, position);
        break;
    default:
        return;
    }
    entity->attributes.entitySpecificAttributes.waveEntity.wave = wave;
}

void SpawnNextWave(Engine *engine)
{
    engine->waveSystem.currentWave++;
    GameWave *wave = &engine->waveSystem.waves[engine->waveSystem.currentWave - 1];

    srand(time(NULL));

    for (int i = 0; i < wave->redEnemiesAmount; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnWaveEntity(engine, position, ENTITY_REDENEMY, wave);
    }
    for (int i = 0; i < wave->blueEnemiesAmount; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnWaveEntity(engine, position, ENTITY_BLUEENEMY, wave);
    }
    for (int i = 0; i < wave->powerupShootingAmount; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnWaveEntity(engine, position, ENTITY_POWERUP_SHOOTING, wave);
    }
    for (int i = 0; i < wave->powerupSpeedAmount; i++)
    {
        int randX = rand() % GetScreenWidth();
        int randY = rand() % GetScreenHeight();
        Vector2 position = (Vector2){randX, randY};
        SpawnWaveEntity(engine, position, ENTITY_POWERUP_SPEED, wave);
    }
}

void CheckWaveEnded(Engine *engine)
{
    GameWave wave = engine->waveSystem.waves[engine->waveSystem.currentWave - 1];
    int currentWave = engine->waveSystem.currentWave;
    if (wave.redEnemiesAmount == 0 && wave.blueEnemiesAmount == 0)
    {
        if (currentWave == WAVES_AMOUNT)
            WinGame(engine);
        else
            SpawnNextWave(engine);
    }
}

void HandleEntityWaveDeath(Engine *engine, Entity *entity, GameWave *wave)
{
    switch (entity->type)
    {
    case ENTITY_REDENEMY:
        wave->redEnemiesAmount--;
        wave->stats.redEnemiesKilled++;
        break;
    case ENTITY_BLUEENEMY:
        wave->blueEnemiesAmount--;
        wave->stats.blueEnemiesKilled++;
        break;
    case ENTITY_POWERUP_SHOOTING:
        wave->powerupShootingAmount--;
        wave->stats.powerupShootingPickedUp++;
        break;
    case ENTITY_POWERUP_SPEED:
        wave->powerupSpeedAmount--;
        wave->powerupShootingAmount++;
        break;
    default:
        break;
    }

    CheckWaveEnded(engine);
}
