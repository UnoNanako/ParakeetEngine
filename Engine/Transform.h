#pragma once
#include "Math/MyMath.h"
#include <memory>
#include <d3d12.h>
#include <wrl.h>

class DirectXCommon;

class Transform {
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon);
	//行列を更新する
	void UpdateMatrix();
	void Bind(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, uint32_t rootParamIndex)const;

	Matrix4x4 GetMatWorld() const { return mMatWorld; }

public:
	Vector3 mScale = { 1.0f,1.0f,1.0f };
	Vector3 mRotate = { 0.0f,0.0f,0.0f };
	Vector3 mTranslate = { 0.0f,0.0f,0.0f };
	//親となるワールド変換へのポインタ
	//ローカル→ワールド変換行列
	Matrix4x4 mMatWorld;
	std::shared_ptr<Transform> mParent = nullptr;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> mWorldMatrixResource;
	Matrix4x4* mWorldMatrixData;
};

