#include "RotateBridge.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "Crank.h"
#include "MyGame.h"
#include "ResourceManager.h"

RotateBridge::RotateBridge(MyGame* myGame)
	:GameObject(myGame){
}

void RotateBridge::Initialize(){
	mTransform.mScale = { 1.0f,1.0f,1.0f };
	mTransform.mRotate = { 0.0f,kPi / 2.0f,0.0f };
	mTransform.mTranslate = { 3.0f,1.0f,12.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Bridge/Bridge.gltf");
}

void RotateBridge::Update(std::shared_ptr<Input> input){
	mTransform.mRotate = { mCrank->GetRotate().x,mCrank->GetRotate().y,mCrank->GetRotate().z};
	Vector3 sideLWorldPos = { 1.3f,0.0f,0.0f };
	Vector3 sideRWorldPos = { -1.3f,0.0f,0.0f };
	Matrix4x4 rotateX = MakeRotateXMatrix(mTransform.mRotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(mTransform.mRotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(mTransform.mRotate.z);
	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateX, rotateY), rotateZ);
	sideLWorldPos = Multiply(sideLWorldPos, rotateMatrix);
	sideRWorldPos = Multiply(sideRWorldPos, rotateMatrix);
	Vector3 WorldPos = mTransform.mTranslate;
	mSideLOBB = CalculateOBB(sideLWorldPos + WorldPos, { 0.2f,2.0f,6.0f });
	mSideROBB = CalculateOBB(sideRWorldPos + WorldPos, { 0.2f,2.0f,6.0f });
	WorldPos.y -= 1.0f;
	mOBB = CalculateOBB(WorldPos, { 1.1f,1.0f,6.0f });
	mTransform.UpdateMatrix();
}

void RotateBridge::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	mModel->Draw(commandList, mTransform);
}

OBB RotateBridge::CalculateOBB(const Vector3& translate, const Vector3& size){
	OBB ret;
	ret.center = translate;
	ret.size = size;
	Matrix4x4 rotateX = MakeRotateXMatrix(mTransform.mRotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(mTransform.mRotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(mTransform.mRotate.z);
	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateX, rotateY), rotateZ);
	ret.axis[0].x = rotateMatrix.m[0][0];
	ret.axis[0].y = rotateMatrix.m[0][1];
	ret.axis[0].z = rotateMatrix.m[0][2];
	ret.axis[1].x = rotateMatrix.m[1][0];
	ret.axis[1].y = rotateMatrix.m[1][1];
	ret.axis[1].z = rotateMatrix.m[1][2];
	ret.axis[2].x = rotateMatrix.m[2][0];
	ret.axis[2].y = rotateMatrix.m[2][1];
	ret.axis[2].z = rotateMatrix.m[2][2];
	return ret;
}
