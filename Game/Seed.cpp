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
	mTransform.mScale = { 0.1f,0.1f,0.1f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Seed/Seed.obj");
}

void Seed::Update(std::shared_ptr<Input> input){
	mLocalAABB.mMin = { -0.1f,-0.1f,-0.1f };
	mLocalAABB.mMax = { 0.1f,0.1f,0.1f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	mTransform.UpdateMatrix();
}

void Seed::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	if (!mIsHit) {
		mModel->Draw(commandList, mTransform);
	}
}
