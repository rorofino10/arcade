#include "audio_engine.h"
#include <stdlib.h>

void InitAudioEngine(AudioEngine *audio_engine)
{
    InitAudioDevice();

    audio_engine->background_music = LoadMusicStream("assets/background_music.mp3");

    audio_engine->soundArray[SOUND_EFFECT_BULLET] = LoadSound("assets/laser.mp3");
    audio_engine->soundArray[SOUND_EFFECT_EXPLOSION] = LoadSound("assets/explosion.wav");
    audio_engine->soundArray[SOUND_EFFECT_POWERUP] = LoadSound("assets/power_up.mp3");

    delayBufferSize = 48000 * 2; // 1 second delay (device sampleRate*channels)
    delayBuffer = (float *)RL_CALLOC(delayBufferSize, sizeof(float));

    PlayMusicStream(audio_engine->background_music);
}

void PlaySoundAudioEngine(AudioEngine *audio_engine, SOUND_EFFECTS sound)
{
    PlaySound(audio_engine->soundArray[sound]);
}

void UpdateAudioEngine(AudioEngine *audio_engine)
{
    UpdateMusicStream(audio_engine->background_music);
}

void PauseMusicAudioEngine(AudioEngine *audio_engine)
{
    PauseMusicStream(audio_engine->background_music);
}
void UnpauseMusicAudioEngine(AudioEngine *audio_engine)
{
    ResumeMusicStream(audio_engine->background_music);
}

void FreeAudioEngine(AudioEngine *audio_engine)
{
    UnloadMusicStream(audio_engine->background_music);

    for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
    {
        UnloadSound(audio_engine->soundArray[i]);
    }

    CloseAudioDevice();
    RL_FREE(delayBuffer);
}
