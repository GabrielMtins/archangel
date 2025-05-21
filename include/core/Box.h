#ifndef BOX_H
#define BOX_H

#include <stdbool.h>
#include "core/Vec2.h"

bool Box_CheckCollisionBoxBox(const Vec2 *a_pos, const Vec2 *a_size, const Vec2 *b_pos, const Vec2 *b_size);

bool Box_SolveCollision(Vec2 *a_pos, const Vec2 *a_size, const Vec2 *b_pos, const Vec2 *b_size);

#endif
