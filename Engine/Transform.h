#pragma once
#include "Math/MyMath.h"
#include <memory>

struct TransformationMatrix {
	Matrix4x4 wvp;
	Matrix4x4 world;
};

struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

//ローカル→ワールド変換行列
Matrix4x4 mMatWorld;

//親となるワールド変換へのポインタ
std::unique_ptr<Transform> mParent = nullptr;

//行列を更新する
void UpdateMatrix();