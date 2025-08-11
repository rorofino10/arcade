#ifndef State_H
#define State_H

typedef enum
{
    STATE_TITLE_SCREEN,
    STATE_PLAYING,
    STATE_LOST,
    STATE_WIN,
    STATE_PAUSED
} GameState;

struct Engine;
void StartGame(struct Engine *engine);
void RestartGame(struct Engine *engine);
void LoseGame(struct Engine *engine);
void WinGame(struct Engine *engine);
void PauseGame(struct Engine *engine);
void UnpauseGame(struct Engine *engine);

#endif
