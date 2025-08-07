#include "title_screen.h"
#include "raylib.h"
#include "raymath.h"
#include "shared/utils.h"

const char *title = "TITLE SCREEN";
const int titleFontSize = 40;

const int subTitleFontSize = titleFontSize / 2;
const char *subTitle = "PRESS ENTER TO CONTINUE";

void HandleInputTitleScreen(Engine *engine)
{
    if (IsKeyDown(KEY_ENTER))
    {
        engine->game_state = STATE_PLAYING;
    }
}

void UpdateTitleScreen(Engine *engine)
{
}

void DrawTitleScreen(Engine *engine)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};

    int titleWidth = MeasureText(title, titleFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){titleWidth, titleFontSize});

    DrawText(title, textPosition.x, textPosition.y, titleFontSize, RAYWHITE);

    Vector2 subTitleSize = (Vector2){MeasureText(subTitle, subTitleFontSize), subTitleFontSize};

    Vector2 subTitlePosition = (Vector2){screenCenter.x, screenCenter.y + titleFontSize + 10};
    subTitlePosition = FromCenteredReturnTopLeftPositionV(subTitlePosition, subTitleSize);
    DrawText(subTitle, subTitlePosition.x, subTitlePosition.y, subTitleFontSize, GRAY);
}
