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

typedef struct audio_engine
{
    Music background_music;
} AudioEngine;

void InitAudioEngine(AudioEngine *audio_engine);
void UpdateAudioEngine(AudioEngine *audio_engine);
void FreeAudioEngine(AudioEngine *audio_engine);

#endif
