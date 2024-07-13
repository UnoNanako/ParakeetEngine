#include "Seed.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"

Seed::Seed(MyGame* myGame)
	:GameObject(myGame){
}

void Seed::Initialize(){
	mTransform.mScale = { 1.0f,1.0f,1.0f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.5f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Seed/Seed.gltf");
	mIsHit = false;
}

void Seed::Update(std::shared_ptr<Input> input){
	mTransform.mRotate.y += 0.05f;
	mLocalAABB.mMin = { -0.5f,-0.5f,-0.5f };
	mLocalAABB.mMax = { 0.5f,0.5f,0.5f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	mTransform.UpdateMatrix();
}

void Seed::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	if (!mIsHit) {
		mModel->Draw(commandList, mTransform);
	}
}
