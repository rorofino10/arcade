#ifndef State_H
#define State_H

typedef enum
{
    STATE_TITLE_SCREEN,
    STATE_PLAYING,
    STATE_LOST,
    STATE_PAUSED
} GameState;

struct Engine;

void HandleInputState(struct Engine *engine);

#endif
