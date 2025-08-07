#include "audio_engine.h"
#include <stdlib.h>

void InitAudioEngine(AudioEngine *audio_engine)
{
    InitAudioDevice();

    audio_engine->background_music = LoadMusicStream("assets/background_music.mp3");

    audio_engine->soundArray[BULLET_SOUND] = LoadSound("assets/laser.mp3");
    audio_engine->soundArray[EXPLOSION_SOUND] = LoadSound("assets/explosion.wav");

    delayBufferSize = 48000 * 2; // 1 second delay (device sampleRate*channels)
    delayBuffer = (float *)RL_CALLOC(delayBufferSize, sizeof(float));

    PlayMusicStream(audio_engine->background_music);
}

void PlaySoundAudioEngine(AudioEngine *audio_engine, SOUNDS sound)
{
    PlaySound(audio_engine->soundArray[sound]);
}

void UpdateAudioEngine(AudioEngine *audio_engine)
{
    UpdateMusicStream(audio_engine->background_music);
}

void FreeAudioEngine(AudioEngine *audio_engine)
{
    UnloadMusicStream(audio_engine->background_music);

    UnloadSound(audio_engine->soundArray[BULLET_SOUND]);

    CloseAudioDevice();
    RL_FREE(delayBuffer);
}
