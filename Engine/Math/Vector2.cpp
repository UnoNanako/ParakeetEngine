#include "Vector2.h"
#include <cmath>

float Length(const Vector2& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}