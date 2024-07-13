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

bool IsCollision(const AABB& a, const OBB& b, CollisionResult& result){
	Vector3 size = (a.mMax - a.mMin) / 2.0f;
	OBB obb;
	obb.center = a.mMin + size;
	obb.size = size;
	if (IsCollision(obb, b, result)) {
		return true;
	}
	return false;
}

bool IsCollision(const OBB& a, const OBB& b, CollisionResult& result){
	//分離軸
	Vector3 axes[15];
	axes[0] = a.axis[0];
	axes[1] = a.axis[1];
	axes[2] = a.axis[2];
	axes[3] = b.axis[0];
	axes[4] = b.axis[1];
	axes[5] = b.axis[2];
	axes[6] = Normalize(Cross(a.axis[0], b.axis[0]));
	axes[7] = Normalize(Cross(a.axis[0], b.axis[1]));
	axes[8] = Normalize(Cross(a.axis[0], b.axis[2]));
	axes[9] = Normalize(Cross(a.axis[1], b.axis[0]));
	axes[10] = Normalize(Cross(a.axis[1], b.axis[1]));
	axes[11] = Normalize(Cross(a.axis[1], b.axis[2]));
	axes[12] = Normalize(Cross(a.axis[2], b.axis[0]));
	axes[13] = Normalize(Cross(a.axis[2], b.axis[1]));
	axes[14] = Normalize(Cross(a.axis[2], b.axis[2]));
	Vector3 d1[3] = {
		a.axis[0] * a.size.x,
		a.axis[1] * a.size.y,
		a.axis[2] * a.size.z
	};
	Vector3 d2[3] = {
		b.axis[0] * b.size.x,
		b.axis[1] * b.size.y,
		b.axis[2] * b.size.z
	};
	Vector3 c1[8] = {
		a.center + d1[0] + d1[1] + d1[2],
		a.center + d1[0] + d1[1] - d1[2],
		a.center + d1[0] - d1[1] + d1[2],
		a.center + d1[0] - d1[1] - d1[2],
		a.center - d1[0] + d1[1] + d1[2],
		a.center - d1[0] + d1[1] - d1[2],
		a.center - d1[0] - d1[1] + d1[2],
		a.center - d1[0] - d1[1] - d1[2]
	};
	Vector3 c2[8] = {
		b.center + d2[0] + d2[1] + d2[2],
		b.center + d2[0] + d2[1] - d2[2],
		b.center + d2[0] - d2[1] + d2[2],
		b.center + d2[0] - d2[1] - d2[2],
		b.center - d2[0] + d2[1] + d2[2],
		b.center - d2[0] + d2[1] - d2[2],
		b.center - d2[0] - d2[1] + d2[2],
		b.center - d2[0] - d2[1] - d2[2]
	};
	float minOverlap = kInfinity;
	Vector3 minAxis;
	for (const auto& axis : axes) {
		if (axis.x > -kEpsilon && axis.x < kEpsilon &&
			axis.y > -kEpsilon && axis.y < kEpsilon &&
			axis.z > -kEpsilon && axis.z < kEpsilon) {
			continue;
		}
		float min1 = (std::numeric_limits<float>::max)();
		float max1 = std::numeric_limits<float>::lowest();
		float min2 = min1;
		float max2 = max1;
		for (uint32_t i = 0; i < 8; ++i) {
			float dist1 = Dot(c1[i], axis);
			min1 = Min(dist1, min1);
			max1 = Max(dist1, max1);
			float dist2 = Dot(c2[i], axis);
			min2 = Min(dist2, min2);
			max2 = Max(dist2, max2);
		}
		float overlap = (max1 - min1) + (max2 - min2) - (Max(max1, max2) - Min(min1, min2));
		if (overlap < 0.0f) {
			return false;
		}
		if (overlap < minOverlap) {
			minOverlap = overlap;
			minAxis = axis;
		}
	}
	result.normal = Normalize(minAxis);
	if (Dot(a.center - b.center, result.normal) < 0.0f) {
		result.normal = -result.normal;
	}
	result.depth = minOverlap;
	return true;
}

AABB CalcWorldAABB(const AABB& localAABB,const Vector3& translate) {
	AABB ret;
	ret.mMax = localAABB.mMax + translate;
	ret.mMin = localAABB.mMin + translate;
	return ret;
}