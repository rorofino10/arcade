#ifndef AudioEngine_H
#define AudioEngine_H

#include <stdio.h>
#include "raylib.h"
static float *delayBuffer = NULL;
static unsigned int delayBufferSize = 0;
static unsigned int delayReadIndex = 2;
static unsigned int delayWriteIndex = 0;

static void AudioProcessEffectLPF(void *buffer, unsigned int frames);   // Audio effect: lowpass filter
static void AudioProcessEffectDelay(void *buffer, unsigned int frames); // Audio effect: delay

typedef enum
{
    SOUND_EFFECT_BULLET,
    SOUND_EFFECT_EXPLOSION,
    SOUND_EFFECT_POWERUP,

    // Count
    SOUND_EFFECT_COUNT
} SOUND_EFFECTS;

typedef struct audio_engine
{
    Music background_music;
    Sound soundArray[SOUND_EFFECT_COUNT];
} AudioEngine;

void InitAudioEngine(AudioEngine *audio_engine);

void UpdateAudioEngine(AudioEngine *audio_engine);

void PlaySoundAudioEngine(AudioEngine *audio_engine, SOUND_EFFECTS sound);

void FreeAudioEngine(AudioEngine *audio_engine);

#endif
