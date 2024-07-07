#include "Sprite.h"
#include "DirectXCommon.h"
#include "Transform.h"
#include "Math/MyMath.h"
#include "3D/VertexData.h"
#include <Windows.h>

void Sprite::Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture){
	//テクスチャ
	mTexture = texture;

	//インデックス
	mIndexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(uint32_t) * 6);
	mIndexBufferView.BufferLocation = mIndexResource->GetGPUVirtualAddress();
	mIndexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	uint32_t* indexData = nullptr;
	mIndexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	indexData[0] = 0; 
	indexData[1] = 1; 
	indexData[2] = 2;
	indexData[3] = 1; 
	indexData[4] = 3; 
	indexData[5] = 2;

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
	vertexData[0].mPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
	vertexData[0].mTexcoord = { 0.0f,0.0f };
	// 右上
	vertexData[1].mPosition = { width, 0.0f, 0.0f, 1.0f };
	vertexData[1].mTexcoord = { 1.0f,0.0f };
	// 左下
	vertexData[2].mPosition = { 0.0f, height, 0.0f, 1.0f };
	vertexData[2].mTexcoord = { 0.0f,1.0f };
	//右下
	vertexData[3].mPosition = { width,height,0.0f,1.0f };
	vertexData[3].mTexcoord = { 1.0f,1.0f };

	//色
	//Sprite用のマテリアルリソースを作る
	mColorResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(Vector4));
	//書き込むためのアドレスを取得
	mColorResource->Map(0, nullptr, reinterpret_cast<void**>(&mColorData));
	*mColorData = { 1.0f,1.0f,1.0f,1.0f };
}

void Sprite::Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,const Transform& transform){
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, mColorResource->GetGPUVirtualAddress());
	transform.Bind(commandList, 1);
	mTexture->Bind(commandList,3);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	commandList->IASetIndexBuffer(&mIndexBufferView);
	commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}
