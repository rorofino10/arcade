#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "entity.h"
#include "engine.h"
#include "audio_engine.h"
int main(int argc, char **argv)
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED);
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    SetTargetFPS(60);
    DisableCursor();

    Engine engine;
    InitEngine(&engine);

    AudioEngine audio_engine;
    InitAudioEngine(&audio_engine);

    while (!WindowShouldClose())
    {
        HandleInputEngine(&engine);

        UpdateEngine(&engine);
        UpdateAudioEngine(&audio_engine);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawEngine(&engine);
        EndDrawing();
    }
    FreeEngine(&engine);
    FreeAudioEngine(&audio_engine);
    return 0;
}
