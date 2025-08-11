#ifndef WAVE_SYSTEM_H
#define WAVE_SYSTEM_H

#define WAVES_AMOUNT 3
struct Engine;
struct Entity;

typedef struct
{
    int redEnemiesKilled;
    int blueEnemiesKilled;
    int powerupShootingPickedUp;
    int powerupSpeedPickedUp;
} GameWaveStats;

typedef struct
{
    int redEnemiesAmount;
    int blueEnemiesAmount;
    int powerupShootingAmount;
    int powerupSpeedAmount;

    float remainingTime;

    GameWaveStats stats;
} GameWave;

typedef struct WaveSystem
{
    int currentWave;
    GameWave waves[WAVES_AMOUNT];
} WaveSystem;

void InitWaveSystem(WaveSystem *waveSystem);
void RestartWaveSystem(WaveSystem *waveSystem);

void UpdateWaveSystem(struct Engine *engine);
void SpawnNextWave(struct Engine *engine);

void HandleEntityWaveDeath(struct Engine *engine, struct Entity *entity, GameWave *wave);

#endif
