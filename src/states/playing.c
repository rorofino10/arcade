#include "playing.h"
#include "raymath.h"

#include "shared/utils.h"
#include "shared/gamepad.h"

#include "engine/collision_system.h"
#include "systems/gameplay.h"

void HandleKeyboardInputPlaying(Engine *engine)
{
    Vector2 velocity = {0};

    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;

    float speed = engine->player->attributes.speed;
    engine->player->velocity = Vector2Scale(velocity, speed);

    Vector2 mousePosition = GetMousePosition();
    Vector2 lookingDirection = Vector2Normalize(Vector2Subtract(mousePosition, engine->player->position));
    engine->player->attributes.entitySpecificAttributes.player.lookingDirection = lookingDirection;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        PlayerShootBullet(engine, lookingDirection);

    if (IsKeyPressed(KEY_P))
        PauseGame(engine);
}

void HandleGamepadInputPlaying(Engine *engine)
{
    float leftStickX = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_LEFT_X);
    float leftStickY = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_LEFT_Y);
    float rightStickX = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_RIGHT_X);
    float rightStickY = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_RIGHT_Y);
    float leftTrigger = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
    float rightTrigger = GetGamepadAxisMovement(engine->gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);

    if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX)
        leftStickX = 0.0f;
    if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY)
        leftStickY = 0.0f;
    if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX)
        rightStickX = 0.0f;
    if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY)
        rightStickY = 0.0f;
    if (leftTrigger < leftTriggerDeadzone)
        leftTrigger = -1.0f;
    if (rightTrigger < rightTriggerDeadzone)
        rightTrigger = -1.0f;

    Vector2 direction = (Vector2){.x = leftStickX, .y = leftStickY};
    float speed = engine->player->attributes.speed;
    engine->player->velocity = Vector2Scale(direction, speed);

    Vector2 lookingDirection = Vector2Normalize((Vector2){.x = rightStickX, .y = rightStickY});
    engine->player->attributes.entitySpecificAttributes.player.lookingDirection = lookingDirection;

    if (IsGamepadButtonDown(engine->gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && (lookingDirection.x != 0.0f || lookingDirection.y != 0.0f))
        PlayerShootBullet(engine, lookingDirection);

    if (IsGamepadButtonPressed(engine->gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    {
        PauseGame(engine);
    }
}

void HandleInputPlaying(Engine *engine)
{
    if (IsGamepadAvailable(engine->gamepad))
    {
        HandleGamepadInputPlaying(engine);
    }
    else
        HandleKeyboardInputPlaying(engine);
}

bool isOffScreen(Entity *entity)
{
    return entity->position.x < 0 || entity->position.y < 0 || entity->position.x > GetScreenWidth() || entity->position.y > GetScreenHeight();
}

void UpdatePlaying(Engine *engine)
{
    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;

        currEntity->position = Vector2Add(currEntity->position, Vector2Scale(currEntity->velocity, GetFrameTime()));
        switch (currEntity->type)
        {
        case ENTITY_BULLET:
            if (isOffScreen(currEntity))
                currEntity->alive = false;
            break;
        case ENTITY_REDENEMY:
            Vector2 direction = Vector2Normalize(Vector2Subtract(engine->player->position, currEntity->position));
            currEntity->velocity = Vector2Scale(direction, currEntity->attributes.speed);
            break;
        case ENTITY_EXPLOSION:
            currEntity->attributes.entitySpecificAttributes.explosion.lifetime -= GetFrameTime();
            if (currEntity->attributes.entitySpecificAttributes.explosion.lifetime < 0.0f)
                currEntity->alive = false;
            break;
        case ENTITY_POWERUP_SPEED:
            break;
        case ENTITY_PLAYER:
            float *powerupSpeedLifetime = &currEntity->attributes.entitySpecificAttributes.player.powerupSpeedLifetime;
            float *powerupShootingLifetime = &currEntity->attributes.entitySpecificAttributes.player.powerupShootingLifetime;
            float *shootingRemainingCooldown = &currEntity->attributes.entitySpecificAttributes.player.shootingRemainingCooldown;
            if (*powerupSpeedLifetime > 0.0f)
            {
                *powerupSpeedLifetime -= GetFrameTime();
            }
            else
            {
                *powerupSpeedLifetime = 0.0f;
                currEntity->attributes.speed = DEFAULT_PLAYER_SPEED;
            }
            if (*powerupShootingLifetime > 0.0f)
            {
                *powerupShootingLifetime -= GetFrameTime();
            }
            else
            {
                *powerupShootingLifetime = 0.0f;
                currEntity->attributes.entitySpecificAttributes.player.shootingCooldown = DEFAULT_PLAYER_SHOOTING_COOLDOWN;
            }
            if (*shootingRemainingCooldown > 0.0f)
            {
                *shootingRemainingCooldown -= GetFrameTime();
            }
            break;
        default:
            break;
        }
    }
    UpdateCollisions(engine);
    UpdateWaveSystem(engine);

    FreeDeadEntitiesFromCollection(&engine->entities);
}

void DrawPlaying(Engine *engine)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);

    Vector2 screenCenter = (Vector2){screenWidth / 2, screenHeight / 2};
    const char *waveText = TextFormat("WAVE %02i", engine->waveSystem.currentWave);
    const int waveTextFontSize = 50;
    int waveTextWidth = MeasureText(waveText, waveTextFontSize);

    Vector2 textPosition = FromCenteredReturnTopLeftPositionV(screenCenter, (Vector2){waveTextWidth, waveTextFontSize});

    DrawText(waveText, textPosition.x, textPosition.y, waveTextFontSize, GRAY);

    const char *remainingTimeText = TextFormat("Remaining time %02.02f s", engine->waveSystem.waves[engine->waveSystem.currentWave - 1].remainingTime);
    const int remainingTimeFontSize = waveTextFontSize / 2;

    Vector2 remainingTimeTextSize = (Vector2){MeasureText(remainingTimeText, remainingTimeFontSize), remainingTimeFontSize};

    Vector2 remainingTimeTextPosition = (Vector2){screenCenter.x, screenCenter.y + waveTextFontSize + 10};
    remainingTimeTextPosition = FromCenteredReturnTopLeftPositionV(remainingTimeTextPosition, remainingTimeTextSize);
    DrawText(remainingTimeText, remainingTimeTextPosition.x, remainingTimeTextPosition.y, remainingTimeFontSize, GRAY);

    for (CollectionNode *curr = engine->entities.head; curr != NULL; curr = curr->next)
    {
        Entity *currEntity = curr->entity;
        Vector2 position = FromCenteredReturnTopLeftPosition(currEntity);

        switch (currEntity->type)
        {
        case ENTITY_PLAYER:
            Vector2 lookingDirection = currEntity->attributes.entitySpecificAttributes.player.lookingDirection;
            float rotation = atan2f(lookingDirection.y, lookingDirection.x) * RAD2DEG;

            Texture2D playerTex = engine->entityTextures[ENTITY_TEXTURE_PLAYER];

            Rectangle src = {0, 0, (float)playerTex.width, (float)playerTex.height};
            Rectangle dest = {position.x, position.y, playerTex.width, playerTex.height};
            Vector2 origin = {(float)playerTex.width / 2, (float)playerTex.height / 2};

            DrawTexturePro(playerTex, src, dest, origin, rotation, WHITE);
            break;
        case ENTITY_REDENEMY:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_REDENEMY], position, WHITE);
            break;
        case ENTITY_BLUEENEMY:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_BLUENEMY], position, WHITE);
            break;
        case ENTITY_BULLET:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_BULLET], position, WHITE);
            break;
        case ENTITY_EXPLOSION:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_EXPLOSION], position, WHITE);
            break;
        case ENTITY_POWERUP_SHOOTING:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_POWERUP_SHOOTING], position, WHITE);
            break;
        case ENTITY_POWERUP_SPEED:
            DrawTextureV(engine->entityTextures[ENTITY_TEXTURE_POWERUP_SPEED], position, WHITE);
            break;
        }
    }
}
