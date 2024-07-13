#include "Easing.h"
#include <cmath>

float Easing::EaseInBack(float mInT){
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return c3 * mInT * mInT * mInT - c1 * mInT * mInT;
}

float Easing::EaseOutBack(float mInT){
	float c1 = 1.70158f;
	float c3 = c1 + 1.0f;
	return float(1 + c3 * pow(mInT - 1, 3) + c1 * pow(mInT - 1, 2));
}

float Easing::EaseInOutCubic(float mInT) {
	return mInT < 0.5f ? 4.0f * mInT * mInT * mInT : 1.0f - pow(-2.0f * mInT + 2.0f, 3.0f) / 2.0f;
}
