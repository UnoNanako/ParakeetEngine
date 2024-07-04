#pragma once
#include "Transform.h"
#include <wrl.h>
#include <d3d12.h>
#include <memory>

class DirectXCommon;
struct Matrix4x4;

class Camera{
public:
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	//TransformのUpdateMatrixを呼び出してから
	void UpdateMatrix();

	void SetRotate(Vector3 rotate) { mRotate = rotate; }
	void SetTranslate(Vector3 translate) { mTranslate = translate; }
	void SetFov(float fov) { mFov = fov; }

	Vector3 GetTranslate() { return mTranslate; }
	Vector3 GetRotate() { return mRotate; }
	Matrix4x4 GetViewMatrix() { return mViewMatrix; }
	Matrix4x4 GetProjectionMatrix() { return mProjectionMatrix; }

protected:
	Vector3 mRotate = { 0.0f,0.0f,0.0f };
	Vector3 mTranslate = { 0.0f,0.0f,0.0f };
	Matrix4x4 mViewMatrix;
	Matrix4x4 mProjectionMatrix;
	float mFov; //視野角(度数法)
};

