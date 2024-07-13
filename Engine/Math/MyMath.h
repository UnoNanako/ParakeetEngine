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

struct OBB {
	Vector3 center; //中心点
	Vector3 axis[3]; //座標軸。正規化必須
	Vector3 size; //座標軸方向の長さの半分。中心から面までの距離

	OBB()
		:center(Vector3::kZero)
		, size(Vector3::kZero)
	{
		axis[0] = Vector3(1.0f, 0.0f, 0.0f);
		axis[1] = Vector3(0.0f, 1.0f, 0.0f);
		axis[2] = Vector3(0.0f, 0.0f, 1.0f);
	}
	OBB(const Vector3& center, const Vector3& size)
		:center(center)
		, size(size)
	{
		axis[0] = Vector3(1.0f, 0.0f, 0.0f);
		axis[1] = Vector3(0.0f, 1.0f, 0.0f);
		axis[2] = Vector3(0.0f, 0.0f, 1.0f);
	}
	Matrix4x4 CreateInverse() const
	{
		Matrix4x4 ret = Matrix4x4::kIdentity;
		ret.m[0][0] = axis[0].x;
		ret.m[0][1] = axis[1].x;
		ret.m[0][2] = axis[2].x;
		ret.m[1][0] = axis[0].y;
		ret.m[1][1] = axis[1].y;
		ret.m[1][2] = axis[2].y;
		ret.m[2][0] = axis[0].z;
		ret.m[2][1] = axis[1].z;
		ret.m[2][2] = axis[2].z;
		ret.m[3][0] = -Dot(center, axis[0]);
		ret.m[3][1] = -Dot(center, axis[1]);
		ret.m[3][2] = -Dot(center, axis[2]);
		return ret;
	}
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

//AABBとAABBの当たり判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2, CollisionResult& result);

bool IsCollision(const AABB& a, const OBB& b, CollisionResult& result);

//OBBとOBBの当たり判定
bool IsCollision(const OBB& a, const OBB& b, CollisionResult& result);


