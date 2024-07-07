#include "MyMath.h"
#include <cmath>

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

bool IsCollision(const AABB& aabb1, const AABB& aabb2, CollisionResult& result){
	if (aabb1.mMin.x <= aabb2.mMax.x && aabb1.mMax.x >= aabb2.mMin.x &&
		aabb1.mMin.y <= aabb2.mMax.y && aabb1.mMax.y >= aabb2.mMin.y &&
		aabb1.mMin.z <= aabb2.mMax.z && aabb1.mMax.z >= aabb2.mMin.z) {
		float x = Min(aabb1.mMax.x - aabb2.mMin.x, aabb2.mMax.x - aabb1.mMin.x);
		float y = Min(aabb1.mMax.y - aabb2.mMin.y, aabb2.mMax.y - aabb1.mMin.y);
		float z = Min(aabb1.mMax.z - aabb2.mMin.z, aabb2.mMax.z - aabb1.mMin.z);
		float minOverlap = kInfinity;
		if (x < minOverlap) {
			minOverlap = x;
			if (aabb1.mMax.x - aabb2.mMin.x < aabb2.mMax.x - aabb1.mMin.x) {
				result.normal = Vector3(-1.0f, 0.0f, 0.0f);
			} else {
				result.normal = Vector3(1.0f, 0.0f, 0.0f);
			}
		}
		if (y < minOverlap) {
			minOverlap = y;
			if (aabb1.mMax.y - aabb2.mMin.y < aabb2.mMax.y - aabb1.mMin.y) {
				result.normal = Vector3(0.0f, -1.0f, 0.0f);
			} else {
				result.normal = Vector3(0.0f, 1.0f, 0.0f);
			}
		}
		if (z < minOverlap) {
			minOverlap = z;
			if (aabb1.mMax.z - aabb2.mMin.z < aabb2.mMax.z - aabb1.mMin.z) {
				result.normal = Vector3(0.0f, 0.0f, -1.0f);
			} else {
				result.normal = Vector3(0.0f, 0.0f, 1.0f);
			}
		}
		result.depth = minOverlap;
		return true;
	}
	return false;
}

AABB CalcWorldAABB(const AABB& localAABB,const Vector3& translate) {
	AABB ret;
	ret.mMax = localAABB.mMax + translate;
	ret.mMin = localAABB.mMin + translate;
	return ret;
}