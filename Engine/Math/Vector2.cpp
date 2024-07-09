#include "Vector2.h"
#include <cmath>

Vector2::Vector2(){
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y){
	this->x = x;
	this->y = y;
}

void Vector2::Normalize(){
	float length = sqrtf((x * x) + (y * y));
	x /= length;
	y /= length;
}

Vector2 Vector2::operator+(Vector2 v){
	Vector2 ret;
	ret.x = x + v.x;
	ret.y = y + v.y;
	return ret;
}

Vector2 Vector2::operator-(Vector2 v){
	Vector2 ret;
	ret.x = x - v.x;
	ret.y = y - v.y;
	return ret;
}

Vector2 Vector2::operator*(float scaler){
	Vector2 ret;
	ret.x = x * scaler;
	ret.y = y * scaler;
	return ret;
}

Vector2 Vector2::operator/(float scaler){
	Vector2 ret;
	ret.x = x / scaler;
	ret.y = y / scaler;
	return ret;
}

void Vector2::operator+=(Vector2 v){
	x += v.x;
	y += v.y;
}

void Vector2::operator-=(Vector2 v){
	x -= v.x;
	y -= v.y;
}

void Vector2::operator*=(float scaler){
	x *= scaler;
	y *= scaler;
}

void Vector2::operator/=(float scaler){
	x /= scaler;
	y /= scaler;
}

float Length(const Vector2& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}
