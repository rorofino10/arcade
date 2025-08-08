#include "win_screen.h"

#include "raylib.h"
#include "raymath.h"
#include "shared/utils.h"

const char *winScreenTitle = "YOU WIN D:";
const int winScreenTitleFontSize = 40;
const Color winScreenTitleColor = RAYWHITE;

const char *winScreenTitleSubTitle = "";
const int winScreenTitleSubTitleFontSize = winScreenTitleFontSize / 2;
const Color winScreenTitleSubTitleColor = GRAY;

const Color winScreenBackgroundColor = SKYBLUE;

void HandleInputWinScreen(Engine *engine)
{
    if (IsKeyPressed(KEY_R))
    {
        // engine->game_state = STATE_PLAYING;
    }
}
void UpdateWinScreen(Engine *engine)
{
}
void DrawWinScreen(Engine *engine)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, winScreenBackgroundColor);

    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};

    int titleWidth = MeasureText(winScreenTitle, winScreenTitleFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){titleWidth, winScreenTitleFontSize});

    DrawText(winScreenTitle, textPosition.x, textPosition.y, winScreenTitleFontSize, winScreenTitleColor);

    Vector2 subTitleSize = (Vector2){MeasureText(winScreenTitleSubTitle, winScreenTitleSubTitleFontSize), winScreenTitleSubTitleFontSize};

    Vector2 subTitlePosition = (Vector2){screenCenter.x, screenCenter.y + winScreenTitleFontSize + 10};
    subTitlePosition = FromCenteredReturnTopLeftPositionV(subTitlePosition, subTitleSize);

    DrawText(winScreenTitleSubTitle, subTitlePosition.x, subTitlePosition.y, winScreenTitleSubTitleFontSize, winScreenTitleSubTitleColor);
}
