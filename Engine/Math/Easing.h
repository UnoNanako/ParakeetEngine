#pragma once
class MyMath;

template <typename T>
T Leap(const T& start, const T& end, float mInT) {
	return start + (end - start) * mInT;
}

namespace Easing {
	float EaseInBack(float mInT);
	float EaseOutBack(float mInT);
	float EaseInOutCubic(float mInT);
}