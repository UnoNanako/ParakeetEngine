#include "Vector3.h"

Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
void Vector3::Normalize() {
	float length = sqrtf((x * x) + (y * y) + (z * z));
	if (length != 0.0f) {
		x /= length;
		y /= length;
		z /= length;
	}
}

bool operator==(const Vector3& v1, const Vector3& v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool operator!=(const Vector3& v1, const Vector3& v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

Vector3 operator-(const Vector3& v) {
	return Vector3(-v.x, -v.y, -v.z);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 operator*(const Vector3& v, float a) {
	return Vector3(v.x * a, v.y * a, v.z * a);
}

Vector3 operator*(float a, const Vector3& v) {
	return Vector3(a * v.x, a * v.y, a * v.z);
}

Vector3 operator/(const Vector3& v, float a) {
	float oneOverA = 1.0f / a;
	return Vector3(v.x * oneOverA, v.y * oneOverA, v.z * oneOverA);
}

Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	v1 = v1 + v2;
	return v1;
}

Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	v1 = v1 - v2;
	return v1;
}

Vector3& operator*=(Vector3& v1, const Vector3& v2) {
	v1 = v1 * v2;
	return v1;
}

Vector3& operator*=(Vector3& v, float a) {
	v = v * a;
	return v;
}

Vector3& operator/=(Vector3& v, float a) {
	float oneOverA = 1.0f / a;
	v = v * oneOverA;
	return v;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Length(const Vector3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float LengthSq(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 ret = v;
	ret.Normalize();
	return ret;
}

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vector3 Multiply(float scalar, const Vector3& v) {
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

Vector3 Multiply(const Vector3& v, const Matrix4x4& m) {
	Vector3 ret;
	ret.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	ret.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	ret.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	return ret;
}

Vector3 Negate(const Vector3& v) {
	return { -v.x, -v.y, -v.z };
}