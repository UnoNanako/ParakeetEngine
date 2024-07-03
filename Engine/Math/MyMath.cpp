#include "MyMath.h"
#include <cmath>

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 ret;
	ret.m[0][0] = 1.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = 1.0f;
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = std::cos(radian);
	ret.m[1][2] = std::sin(radian);
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = -std::sin(radian);
	ret.m[2][2] = std::cos(radian);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = std::cos(radian);
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = -std::sin(radian);
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = std::sin(radian);
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = std::cos(radian);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 ret;
	ret.m[0][0] = std::cos(radian);
	ret.m[0][1] = std::sin(radian);
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = -std::sin(radian);
	ret.m[1][1] = std::cos(radian);
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = 1.0f;
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = 0.0f;
	ret.m[3][3] = 1.0f;
	return ret;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 ret;
	ret.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
		m1.m[0][3] * m2.m[3][0];
	ret.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
		m1.m[0][3] * m2.m[3][1];
	ret.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
		m1.m[0][3] * m2.m[3][2];
	ret.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
		m1.m[0][3] * m2.m[3][3];

	ret.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
		m1.m[1][3] * m2.m[3][0];
	ret.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
		m1.m[1][3] * m2.m[3][1];
	ret.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
		m1.m[1][3] * m2.m[3][2];
	ret.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
		m1.m[1][3] * m2.m[3][3];

	ret.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
		m1.m[2][3] * m2.m[3][0];
	ret.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
		m1.m[2][3] * m2.m[3][1];
	ret.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
		m1.m[2][3] * m2.m[3][2];
	ret.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
		m1.m[2][3] * m2.m[3][3];

	ret.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
		m1.m[3][3] * m2.m[3][0];
	ret.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
		m1.m[3][3] * m2.m[3][1];
	ret.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
		m1.m[3][3] * m2.m[3][2];
	ret.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
		m1.m[3][3] * m2.m[3][3];
	return ret;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	// clang-format off
	float determinant = +m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	Matrix4x4 ret;
	float recpDeterminant = 1.0f / determinant;
	ret.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	ret.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	ret.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
	ret.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * recpDeterminant;

	ret.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	ret.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	ret.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
	ret.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * recpDeterminant;

	ret.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
	ret.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
	ret.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * recpDeterminant;
	ret.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * recpDeterminant;

	ret.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
	ret.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
	ret.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) * recpDeterminant;
	ret.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * recpDeterminant;

	return ret;
	// clang-format on
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 ret = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));
	ret.m[0][0] *= scale.x;
	ret.m[0][1] *= scale.x;
	ret.m[0][2] *= scale.x;

	ret.m[1][0] *= scale.y;
	ret.m[1][1] *= scale.y;
	ret.m[1][2] *= scale.y;

	ret.m[2][0] *= scale.z;
	ret.m[2][1] *= scale.z;
	ret.m[2][2] *= scale.z;

	ret.m[3][0] = translate.x;
	ret.m[3][1] = translate.y;
	ret.m[3][2] = translate.z;
	return ret;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 ret;
	ret.m[0][0] = 2.0f / (right - left);
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 2.0f / (top - bottom);
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = -2.0f / (farClip - nearClip);
	ret.m[2][3] = 0.0f;
	ret.m[3][0] = -(right + left) / (right - left);
	ret.m[3][1] = -(top + bottom) / (top - bottom);
	ret.m[3][2] = -(farClip + nearClip) / (farClip - nearClip);
	ret.m[3][3] = 1.0f;
	return ret;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip){
	Matrix4x4 ret;
	float dot = farClip * nearClip;
	float tan = std::tan(fovY / 2.0f);
	ret.m[0][0] = 1.0f / (aspectRatio * tan);
	ret.m[0][1] = 0.0f;
	ret.m[0][2] = 0.0f;
	ret.m[0][3] = 0.0f;
	ret.m[1][0] = 0.0f;
	ret.m[1][1] = 1.0f / tan;
	ret.m[1][2] = 0.0f;
	ret.m[1][3] = 0.0f;
	ret.m[2][0] = 0.0f;
	ret.m[2][1] = 0.0f;
	ret.m[2][2] = farClip / (farClip - nearClip);
	ret.m[2][3] = 1.0f;
	ret.m[3][0] = 0.0f;
	ret.m[3][1] = 0.0f;
	ret.m[3][2] = -dot / (farClip - nearClip);
	ret.m[3][3] = 0.0f;
	return ret;
}

Matrix3x3 Transpose(const Matrix3x3& matrix) {
	Matrix3x3 ret;
	ret.m[0][0] = matrix.m[0][0];
	ret.m[0][1] = matrix.m[1][0];
	ret.m[0][2] = matrix.m[2][0];
	ret.m[1][0] = matrix.m[0][1];
	ret.m[1][1] = matrix.m[1][1];
	ret.m[1][2] = matrix.m[2][1];
	ret.m[2][0] = matrix.m[0][2];
	ret.m[2][1] = matrix.m[1][2];
	ret.m[2][2] = matrix.m[2][2];
	return ret;
}

Matrix4x4 Transpose(const Matrix4x4& matrix) {
	Matrix4x4 ret;
	ret.m[0][0] = matrix.m[0][0];
	ret.m[0][1] = matrix.m[1][0];
	ret.m[0][2] = matrix.m[2][0];
	ret.m[0][3] = matrix.m[3][0];

	ret.m[1][0] = matrix.m[0][1];
	ret.m[1][1] = matrix.m[1][1];
	ret.m[1][2] = matrix.m[2][1];
	ret.m[1][3] = matrix.m[3][1];

	ret.m[2][0] = matrix.m[0][2];
	ret.m[2][1] = matrix.m[1][2];
	ret.m[2][2] = matrix.m[2][2];
	ret.m[2][3] = matrix.m[3][2];

	ret.m[3][0] = matrix.m[0][3];
	ret.m[3][1] = matrix.m[1][3];
	ret.m[3][2] = matrix.m[2][3];
	ret.m[3][3] = matrix.m[3][3];

	return ret;
}
