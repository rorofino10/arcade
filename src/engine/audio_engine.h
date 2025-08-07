#ifndef AudioEngine_H
#define AudioEngine_H

#include <stdio.h>
#include "raylib.h"
static float *delayBuffer = NULL;
static unsigned int delayBufferSize = 0;
static unsigned int delayReadIndex = 2;
static unsigned int delayWriteIndex = 0;

#define MAX_SOUNDS 10

static void AudioProcessEffectLPF(void *buffer, unsigned int frames);   // Audio effect: lowpass filter
static void AudioProcessEffectDelay(void *buffer, unsigned int frames); // Audio effect: delay

typedef enum
{
    BULLET_SOUND,
    EXPLOSION_SOUND,
} SOUNDS;

typedef struct audio_engine
{
    Music background_music;
    Sound soundArray[MAX_SOUNDS];
} AudioEngine;

void InitAudioEngine(AudioEngine *audio_engine);

void UpdateAudioEngine(AudioEngine *audio_engine);

void PlaySoundAudioEngine(AudioEngine *audio_engine, SOUNDS sound);

void FreeAudioEngine(AudioEngine *audio_engine);

#endif
