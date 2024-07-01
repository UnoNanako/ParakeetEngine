#include "Sprite.h"
#include "DirectXCommon.h"
#include "Material.h"
#include "Transform.h"
#include "VertexData.h"
#include "Math/MyMath.h"
#include <Windows.h>

void Sprite::Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture){
	//テクスチャ
	mTexture = texture;

	//インデックス
	mIndexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(uint32_t) * 6);
	mIndexBufferView.BufferLocation = mIndexResource->GetGPUVirtualAddress();
	mIndexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	mIndexData = nullptr;
	mIndexResource->Map(0, nullptr, reinterpret_cast<void**>(&mIndexData));
	mIndexData[0] = 0; 
	mIndexData[1] = 1; 
	mIndexData[2] = 2;
	mIndexData[3] = 1; 
	mIndexData[4] = 3; 
	mIndexData[5] = 2;

	//頂点
	mVertexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(VertexData) * 4);
	mVertexBufferView.BufferLocation = mVertexResource->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = sizeof(VertexData) * 4;
	mVertexBufferView.StrideInBytes = sizeof(VertexData);

	// 頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	mVertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	float width = float(mTexture->GetWidth());
	float height = float(mTexture->GetHeight());
	// 左上
	vertexData[0].position = { 0.0f, 0.0f, 0.0f, 1.0f };
	vertexData[0].texcoord = { 0.0f,0.0f };
	// 右上
	vertexData[1].position = { width, 0.0f, 0.0f, 1.0f };
	vertexData[1].texcoord = { 1.0f,0.0f };
	// 左下
	vertexData[2].position = { 0.0f, height, 0.0f, 1.0f };
	vertexData[2].texcoord = { 0.0f,1.0f };
	//右下
	vertexData[3].position = { width,height,0.0f,1.0f };
	vertexData[3].texcoord = { 1.0f,1.0f };

	//色
	//Sprite用のマテリアルリソースを作る
	mMaterialResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(Vector4));
	//書き込むためのアドレスを取得
	mMaterialResource->Map(0, nullptr, reinterpret_cast<void**>(&mMaterialData));
	*mMaterialData = { 1.0f,1.0f,1.0f,1.0f };
}

void Sprite::Update(){
	
}

void Sprite::Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,const Transform& transform){
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, mMaterialResource->GetGPUVirtualAddress());
	transform.Bind(commandList, 1);
	mTexture->Bind(commandList,3);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	commandList->IASetIndexBuffer(&mIndexBufferView);
	commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}
