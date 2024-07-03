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

const float kPi = std::numbers::pi_v<float>;
const float kPiOver2 = kPi / 2.0f; //π/2
const float kInfinity = std::numeric_limits<float>::infinity(); //無限
const float kEpsilon = std::numeric_limits<float>::epsilon();

float Length(const Vector3& v);

Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 MakeAffineMatrix(const Vector3& scale,const Vector3& rotate,const Vector3& translate);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

Matrix3x3 Transpose(const Matrix3x3& matrix);

Matrix4x4 Transpose(const Matrix4x4& matrix);

