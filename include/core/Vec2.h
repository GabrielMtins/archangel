#ifndef VEC2_H
#define VEC2_H

typedef struct {
	float x, y;
} Vec2;

void Vec2_Add(Vec2 *result, const Vec2 *a, const Vec2 *b);

void Vec2_Sub(Vec2 *result, const Vec2 *a, const Vec2 *b);

void Vec2_Mul(Vec2 *result, const Vec2 *a, float m);

int Vec2_Div(Vec2 *result, const Vec2 *a, float m);

float Vec2_Dot(const Vec2 *a, const Vec2 *b);

float Vec2_LengthSqr(const Vec2 *a);

float Vec2_Length(const Vec2 *a);

int Vec2_Normalize(Vec2 *result, const Vec2 *a);

#endif
