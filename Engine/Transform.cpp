#include "Transform.h"
#include "DirectXCommon.h"

void Transform::Create(std::shared_ptr<DirectXCommon> dxCommon){
	//Transform
	//Sprite用のTransformMatrix用のリソースを作る。Matrix4x4。1つ分のサイズを用意する
	mWorldMatrixResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(Matrix4x4));
	//書き込むためのアドレスを取得
	mWorldMatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&mWorldMatrixData));
	//単位行列を書き込んでおく
	*mWorldMatrixData = MakeIdentity4x4();
}

void Transform::UpdateMatrix(){
	Matrix4x4 worldMatrix = MakeAffineMatrix(mScale,mRotate,mTranslate);
	*mWorldMatrixData = worldMatrix;
}

void Transform::Bind(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, uint32_t rootParamIndex)const{
	commandList->SetGraphicsRootConstantBufferView(rootParamIndex, mWorldMatrixResource->GetGPUVirtualAddress());
}
