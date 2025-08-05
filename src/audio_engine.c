#include "audio_engine.h"
#include <stdlib.h>

void InitAudioEngine(AudioEngine *audio_engine)
{
    InitAudioDevice();

    audio_engine->background_music = LoadMusicStream("assets/background_music.mp3");

    delayBufferSize = 48000 * 2; // 1 second delay (device sampleRate*channels)
    delayBuffer = (float *)RL_CALLOC(delayBufferSize, sizeof(float));

    PlayMusicStream(audio_engine->background_music);
}

void UpdateAudioEngine(AudioEngine *audio_engine)
{
    UpdateMusicStream(audio_engine->background_music);
}

void FreeAudioEngine(AudioEngine *audio_engine)
{
    UnloadMusicStream(audio_engine->background_music);
    CloseAudioDevice();
    RL_FREE(delayBuffer);
}
