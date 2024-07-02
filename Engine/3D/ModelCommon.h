#pragma once
#include "Math/MyMath.h"
#include <wrl.h>
#include <memory>
#include <d3d12.h>

class DirectXCommon;

//モデル共通部
class ModelCommon{
public:
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	void Finalize();
	void PreDraw(std::shared_ptr<DirectXCommon> dxCommon);
	void PostDraw(std::shared_ptr<DirectXCommon> dxCommon);

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> mGraphicsPipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource> mViewProjectionMatrixResource;
	Matrix4x4* mViewProjectionMatrixData;
};

