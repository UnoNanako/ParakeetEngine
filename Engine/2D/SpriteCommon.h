#pragma once
#include <wrl.h>
#include <memory>
#include <d3d12.h>

class DirectXCommon;

class SpriteCommon{
public:
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	void Finalize();
	void PreDraw(std::shared_ptr<DirectXCommon> dxCommon);
	void PostDraw(std::shared_ptr<DirectXCommon> dxCommon);

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> mGraphicsPipelineState;
};

