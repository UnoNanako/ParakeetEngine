#pragma once
struct Matrix4x4 {
	float m[4][4];
	Matrix4x4() { 
	}
	Matrix4x4(float m[4][4]) {
		memcpy(this->m, m, sizeof(float) * 16);
	}
	static const Matrix4x4 kIdentity;
};