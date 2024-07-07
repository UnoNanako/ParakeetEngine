#pragma once
#include <cmath>
#include "Matrix4x4.h"

struct Vector3 {
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float x, float y, float z);
	void Normalize();
	static const Vector3 kZero;
	static const Vector3 kOne;
};

bool operator==(const Vector3& v1, const Vector3& v2);

bool operator!=(const Vector3& v1, const Vector3& v2);

Vector3 operator-(const Vector3& v);

Vector3 operator+(const Vector3& v1, const Vector3& v2);

Vector3 operator-(const Vector3& v1, const Vector3& v2);

Vector3 operator*(const Vector3& v1, const Vector3& v2);

Vector3 operator*(const Vector3& v, float a);

Vector3 operator*(float a, const Vector3& v);

Vector3 operator/(const Vector3& v, float a);

Vector3& operator+=(Vector3& v1, const Vector3& v2);

Vector3& operator-=(Vector3& v1, const Vector3& v2);

Vector3& operator*=(Vector3& v1, const Vector3& v2);

Vector3& operator*=(Vector3& v, float a);

Vector3& operator/=(Vector3& v, float a);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

float LengthSq(const Vector3& v);

Vector3 Normalize(const Vector3& v);

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(float scalar, const Vector3& v);

Vector3 Multiply(const Vector3& v, const Matrix4x4& m);

Vector3 Negate(const Vector3& v);