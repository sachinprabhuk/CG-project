#ifndef VECTOR
#define VECTOR

typedef struct
{
	float x, y;
} Vector2;

Vector2 *getVector(float x, float y);

Vector2 *vecGetSub(Vector2 *vec1, Vector2 *vec2);

float vecGetMag(Vector2 *vec);

void vecMult(Vector2 *vec, float val);

Vector2 *vecGetAdd(Vector2 *vec1, Vector2 *vec2);

void vecAddAngle(Vector2 *vec, float angleRadian);

#endif