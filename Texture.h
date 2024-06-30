#pragma once
#include "Externals/DirectXTex/DirectXTex.h"
#include <string>
#include <d3d12.h>
#include <wrl.h>
#include <memory>

class DirectXCommon;

class Texture{
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath);
	void Bind(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	uint32_t GetWidth() { return mWidth; }
	uint32_t GetHeight() { return mHeight; }

private:
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr<ID3D12Device> device, const DirectX::TexMetadata& metadata);
	void UploadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);

	Microsoft::WRL::ComPtr<ID3D12Resource> mResource;
	uint32_t mWidth;
	uint32_t mHeight;
	D3D12_GPU_DESCRIPTOR_HANDLE mSrvHandleGPU;
};

