#include "core/Box.h"
#include <math.h>
#include <stddef.h>

bool Box_CheckCollisionBoxBox(const Vec2 *a_pos, const Vec2 *a_size, const Vec2 *b_pos, const Vec2 *b_size){
	if(a_pos->x + a_size->x < b_pos->x)
		return false;

	if(a_pos->y + a_size->y < b_pos->y)
		return false;

	if(b_pos->x + b_size->x < a_pos->x)
		return false;

	if(b_pos->y + b_size->y < a_pos->y)
		return false;

	return true;
}

bool Box_SolveCollision(Vec2 *a_pos, const Vec2 *a_size, const Vec2 *b_pos, const Vec2 *b_size, bool *solved_x_axis){
	float dir_x = 9999.0f, dir_y = 9999.0f;

	if(!Box_CheckCollisionBoxBox(a_pos, a_size, b_pos, b_size)){
		return false;
	}

	if(a_pos->x < b_pos->x + b_size->x && a_pos->x + a_size->x > b_pos->x + b_size->x)
		dir_x = b_pos->x + b_size->x - a_pos->x;
	else if(a_pos->x + a_size->x > b_pos->x && a_pos->x < b_pos->x)
		dir_x = b_pos->x - (a_pos->x + a_size->x);

	if(a_pos->y < b_pos->y + b_size->y && a_pos->y + a_size->y > b_pos->y + b_size->y)
		dir_y = b_pos->y + b_size->y - a_pos->y;
	else if(a_pos->y + a_size->y > b_pos->y && a_pos->y < b_pos->y)
		dir_y = b_pos->y - (a_pos->y + a_size->y);

	dir_x *= 1.01f;
	dir_y *= 1.01f;

	if(fabsf(dir_x) < fabsf(dir_y)){
		a_pos->x += dir_x;

		if(solved_x_axis != NULL)
			*solved_x_axis = true;
	}
	else{
		a_pos->y += dir_y;

		if(solved_x_axis != NULL)
			*solved_x_axis = false;
	}

	return true;
}
