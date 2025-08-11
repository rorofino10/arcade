#include "state.h"
#include "engine/engine.h"
#include "systems/gameplay.h"

void StartGame(Engine *engine)
{
    engine->game_state = STATE_PLAYING;

    InitEntityCollection(&engine->entities);
    SpawnPlayer(engine, (Vector2){0, 0});
    SpawnNextWave(engine);
}

void RestartGame(Engine *engine)
{
    FreeEntityCollection(&engine->entities);
    RestartWaveSystem(&engine->waveSystem);
    RestartAudioEngine(&engine->audio_engine);

    StartGame(engine);
}

void LoseGame(Engine *engine)
{
    engine->game_state = STATE_LOST;
    PauseMusicAudioEngine(&engine->audio_engine);
}

void WinGame(Engine *engine)
{
    engine->game_state = STATE_WIN;
    PauseMusicAudioEngine(&engine->audio_engine);
}
void PauseGame(Engine *engine)
{
    engine->game_state = STATE_PAUSED;
    PauseMusicAudioEngine(&engine->audio_engine);
}
void UnpauseGame(Engine *engine)
{
    engine->game_state = STATE_PLAYING;
    UnpauseMusicAudioEngine(&engine->audio_engine);
}
