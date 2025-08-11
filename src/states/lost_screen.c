#include "lost_screen.h"

#include "raylib.h"
#include "raymath.h"
#include "shared/utils.h"

#include "state.h"

const char *lostScreenTitle = "YOU LOST D:";
const int lostScreenTitleFontSize = 40;
const Color lostScreenTitleColor = RAYWHITE;

const char *lostScreenTitleSubTitle = "PRESS R TO RESTART";
const int lostScreenTitleSubTitleFontSize = lostScreenTitleFontSize / 2;
const Color lostScreenTitleSubTitleColor = GRAY;

const Color lostScreenBackgroundColor = RED;

void HandleInputLostScreen(Engine *engine)
{
    if (IsKeyPressed(KEY_R))
    {
        RestartGame(engine);
    }
}
void UpdateLostScreen(Engine *engine)
{
}
void DrawLostScreen(Engine *engine)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, lostScreenBackgroundColor);

    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};

    int titleWidth = MeasureText(lostScreenTitle, lostScreenTitleFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){titleWidth, lostScreenTitleFontSize});

    DrawText(lostScreenTitle, textPosition.x, textPosition.y, lostScreenTitleFontSize, lostScreenTitleColor);

    Vector2 subTitleSize = (Vector2){MeasureText(lostScreenTitleSubTitle, lostScreenTitleSubTitleFontSize), lostScreenTitleSubTitleFontSize};

    Vector2 subTitlePosition = (Vector2){screenCenter.x, screenCenter.y + lostScreenTitleFontSize + 10};
    subTitlePosition = FromCenteredReturnTopLeftPositionV(subTitlePosition, subTitleSize);

    DrawText(lostScreenTitleSubTitle, subTitlePosition.x, subTitlePosition.y, lostScreenTitleSubTitleFontSize, lostScreenTitleSubTitleColor);
}
