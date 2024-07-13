#include "Skydome.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "3D/ParticleCommon.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"
#include "3D/ParticleManager.h"
#include "PlayerCamera.h"

Skydome::Skydome(MyGame* myGame)
	:GameObject(myGame){
}

void Skydome::Initialize(){
	mTransform.mScale = { 1.0f,1.0f,1.0f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Skydome/sky.obj");
}

void Skydome::Update(std::shared_ptr<Input> input){
	mTransform.UpdateMatrix();
}

void Skydome::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	mModel->Draw(commandList, mTransform);
}
