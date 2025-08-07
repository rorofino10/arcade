#include "utils.h"
#include "raymath.h"

Vector2 centeredPosition(Entity *entity)
{
    (Vector2){entity->position.x - entity->attributes.size.x / 2, entity->position.y - entity->attributes.size.y / 2};
}

Vector2 FromCenteredReturnTopLeftPositionV(Vector2 center, Vector2 size)
{
    return (Vector2){
        center.x - size.x / 2.0f,
        center.y - size.y / 2.0f};
}

Vector2 FromCenteredReturnTopLeftPosition(Entity *entity)
{
    Vector2 center = entity->position;
    Vector2 size = entity->attributes.size;
    return FromCenteredReturnTopLeftPositionV(center, size);
}
