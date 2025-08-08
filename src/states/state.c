#include "state.h"
#include "engine/engine.h"

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
