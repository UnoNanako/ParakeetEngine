#pragma once
#include "Transform.h"
#include "2D/Texture.h"
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <memory>

class DirectXCommon;
struct Material;

class Sprite{
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture);
	void Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,const Transform& transform);

private:
	std::shared_ptr<Texture> mTexture;
	Microsoft::WRL::ComPtr<ID3D12Resource> mVertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mIndexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mColorResource;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView{};
	Vector4* mColorData;
};

