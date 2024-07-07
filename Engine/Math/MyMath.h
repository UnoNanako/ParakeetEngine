#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>
#include <limits>

template <class T>
inline T Max(const T& a, const T& b) {
	return a > b ? a : b;
}
template <class T>
inline T Min(const T& a, const T& b) {
	return a < b ? a : b;
}
template <typename T>
inline T Lerp(const T& a, const T& b, float mInT) {
	return (1.0f - mInT) * a + mInT * b;
}

struct AABB {
	Vector3 mMin;
	Vector3 mMax;
};

struct CollisionResult {
	bool isColliding;
	float depth;
	Vector3 normal;
};

AABB CalcWorldAABB(const AABB& localAABB, const Vector3& translate);

const float kPi = std::numbers::pi_v<float>;
const float kPiOver2 = kPi / 2.0f; //π/2
const float kInfinity = std::numeric_limits<float>::infinity(); //無限
const float kEpsilon = std::numeric_limits<float>::epsilon();

float Length(const Vector3& v);

Matrix3x3 Transpose(const Matrix3x3& matrix);

bool IsCollision(const AABB& aabb1, const AABB& aabb2, CollisionResult& result);


