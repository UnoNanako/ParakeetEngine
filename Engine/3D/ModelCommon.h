#pragma once
#include "Math/MyMath.h"
#include <wrl.h>
#include <memory>
#include <d3d12.h>

class DirectXCommon;
class Camera;

//平行光源(Directional Light)
struct DirectionalLight {
	Vector4 mColor; //ライトの色
	Vector3 mDirection; //ライトの向き
	float mIntensity; //輝度
};

//定数(シェーダー側と合わせる)
struct DirectionalLightForGPU {
	Vector4 mColor;
	Vector3 mDirection;
	float mIntensity;
};

//モデル共通部
class ModelCommon{
public:
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	void Finalize();
	void PreDraw(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Camera> camera);
	void PostDraw(std::shared_ptr<DirectXCommon> dxCommon);

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> mGraphicsPipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource> mViewProjectionMatrixResource;
	Matrix4x4* mViewProjectionMatrixData;

	//DirectionalLight
	DirectionalLight mDirectionalLight;
	Microsoft::WRL::ComPtr<ID3D12Resource> mDirectionalLightResource;
	DirectionalLightForGPU* mDirectionalLightData;

	//CameraPos
	Vector3* mCameraData = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> mCameraResource;
};

