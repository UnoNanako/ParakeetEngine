#pragma once
#include "Math/MyMath.h"
#include <d3d12.h>
#include <wrl.h>
#include <memory>

class DirectXCommon;
class Camera;

class ParticleCommon{
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
};


