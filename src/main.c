#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "entity.h"

#include "engine/engine.h"

int main(int argc, char **argv)
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED);
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    SetTargetFPS(60);
    // DisableCursor();

    Engine engine;
    InitEngine(&engine);

    while (!WindowShouldClose())
    {
        HandleInputEngine(&engine);

        UpdateEngine(&engine);

        DrawEngine(&engine);

        DrawText(TextFormat("%d", GetFPS()), 10, 10, 20, DARKGRAY);
    }
    FreeEngine(&engine);
    return 0;
}
