#pragma once
#include <cmath>

struct Vector3 {
	float x;
	float y;
	float z;
	Vector3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Normalize() {
		float length = sqrtf((x * x) + (y * y) + (z * z));
		if (length != 0.0f) {
			x /= length;
			y /= length;
			z /= length;
		}
	}
	static const Vector3 kZero;
	static const Vector3 kOne;
};
inline bool operator==(const Vector3& v1, const Vector3& v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

inline bool operator!=(const Vector3& v1, const Vector3& v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

inline Vector3 operator-(const Vector3& v) {
	return Vector3(-v.x, -v.y, -v.z);
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector3 operator*(const Vector3& v, float a) {
	return Vector3(v.x * a, v.y * a, v.z * a);
}

inline Vector3 operator*(float a, const Vector3& v) {
	return Vector3(a * v.x, a * v.y, a * v.z);
}

inline Vector3 operator/(const Vector3& v, float a) {
	float oneOverA = 1.0f / a;
	return Vector3(v.x * oneOverA, v.y * oneOverA, v.z * oneOverA);
}

inline Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	v1 = v1 + v2;
	return v1;
}

inline Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	v1 = v1 - v2;
	return v1;
}

inline Vector3& operator*=(Vector3& v1, const Vector3& v2) {
	v1 = v1 * v2;
	return v1;
}

inline Vector3& operator*=(Vector3& v, float a) {
	v = v * a;
	return v;
}

inline Vector3& operator/=(Vector3& v, float a) {
	float oneOverA = 1.0f / a;
	v = v * oneOverA;
	return v;
}

inline Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Length(const Vector3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float LengthSq(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline Vector3 Normalize(const Vector3& v) {
	Vector3 ret = v;
	ret.Normalize();
	return ret;
}

Vector2 ToVector2(const Vector3 v);
Vector3 ToVector3(const Vector2 v);

inline Vector3 Add(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
inline Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
inline Vector3 Multiply(float scalar, const Vector3& v) {
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

inline Vector3 Negate(const Vector3& v) {
	return { -v.x, -v.y, -v.z };
}