#include "paused_screen.h"
#include "raylib.h"
#include "raymath.h"
#include "shared/utils.h"

const char *pausedScreenTitle = "PAUSED SCREEN";
const int pausedScreenTitleFontSize = 40;
const Color pausedScreenTitleColor = RAYWHITE;

const char *pausedScreenTitleSubTitle = "PRESS P TO UNPAUSE";
const int pausedScreenTitleSubTitleFontSize = pausedScreenTitleFontSize / 2;
const Color pausedScreenTitleSubTitleColor = BLACK;

const Color pausedScreenBackgroundColor = GRAY;

void HandleInputPausedScreen(Engine *engine)
{
    if (IsKeyPressed(KEY_P))
    {
        UnpauseGame(engine);
    }
}
void UpdatePausedScreen(Engine *engine)
{
}
void DrawPausedScreen(Engine *engine)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, pausedScreenBackgroundColor);

    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};

    int titleWidth = MeasureText(pausedScreenTitle, pausedScreenTitleFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){titleWidth, pausedScreenTitleFontSize});

    DrawText(pausedScreenTitle, textPosition.x, textPosition.y, pausedScreenTitleFontSize, pausedScreenTitleColor);

    Vector2 subTitleSize = (Vector2){MeasureText(pausedScreenTitleSubTitle, pausedScreenTitleSubTitleFontSize), pausedScreenTitleSubTitleFontSize};

    Vector2 subTitlePosition = (Vector2){screenCenter.x, screenCenter.y + pausedScreenTitleFontSize + 10};
    subTitlePosition = FromCenteredReturnTopLeftPositionV(subTitlePosition, subTitleSize);

    DrawText(pausedScreenTitleSubTitle, subTitlePosition.x, subTitlePosition.y, pausedScreenTitleSubTitleFontSize, pausedScreenTitleSubTitleColor);
}
