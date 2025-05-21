#include "core/Vec2.h"

#include <math.h>

void Vec2_Add(Vec2 *result, const Vec2 *a, const Vec2 *b){
	result->x = a->x + b->x;
	result->y = a->y + b->y;
}

void Vec2_Sub(Vec2 *result, const Vec2 *a, const Vec2 *b){
	result->x = a->x - b->x;
	result->y = a->y - b->y;
}

void Vec2_Mul(Vec2 *result, const Vec2 *a, float m){
	result->x = a->x * m;
	result->y = a->y * m;
}

int Vec2_Div(Vec2 *result, const Vec2 *a, float m){
	if(m == 0)
		return -1;

	result->x = a->x / m;
	result->y = a->y / m;

	return 0;
}

float Vec2_Dot(const Vec2 *a, const Vec2 *b){
	return a->x * b->x + a->y * b->y;
}

float Vec2_LengthSqr(const Vec2 *a){
	return a->x * a->x + a->y * a->y;
}

float Vec2_Length(const Vec2 *a){
	return sqrtf(Vec2_LengthSqr(a));
}

int Vec2_Normalize(Vec2 *result, const Vec2 *a){
	return Vec2_Div(result, a, Vec2_Length(a));
}
