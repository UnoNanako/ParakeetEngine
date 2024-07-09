#pragma once
struct Vector2 {
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	void Normalize();
	//オーバーロード
	Vector2 operator+(Vector2 v);

	Vector2 operator-(Vector2 v);

	Vector2 operator*(float scaler);

	Vector2 operator/(float scaler);

	void operator+=(Vector2 v);

	void operator-=(Vector2 v);

	void operator*=(float scaler);

	void operator/=(float scaler);
};

float Length(const Vector2& v);