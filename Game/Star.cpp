#include "Star.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "3D/ParticleCommon.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"

Star::Star(MyGame* myGame)
	:GameObject(myGame) {
}

void Star::Initialize(){
	mTransform.mScale = { 0.2f,0.2f,0.2f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { -3.5f,5.5f,20.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Star/Star.obj");
	/*mParticle = std::make_unique<ParticleList>();
	mParticle->Create(mDxCommon, "resources/Particle/circle.png");
	mParticle->SetTranslateMin({ -1.0f,-1.0f,-1.0f });
	mParticle->SetTranslateMax({ 1.0f,1.0f,1.0f });
	mParticle->SetVelocityMin({ -5.0f,5.0f,-5.0f });
	mParticle->SetVelocityMax({ 5.0f,6.0f,5.0f });
	mParticle->SetColorMin({ 150.0f / 255.0f,150.0f / 255.0f,0.0f });
	mParticle->SetColorMax({ 1.0f,1.0f,0.0f });
	mParticle->SetLifeTImeMin(0.5f);
	mParticle->SetLifeTimeMax(1.0f);*/

	mIsPlayerHit = false;
}

void Star::Update(std::shared_ptr<Input> input){
	mTransform.mRotate.y += 0.05f;
	mLocalAABB.mMin = { -0.2f,-0.5f,-0.2f };
	mLocalAABB.mMax = { 0.2f,0.2f,0.2f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	/*mParticle->Update();
	mParticle->SetEmitTranslate({ mTransform.translate.x,mTransform.translate.y,mTransform.translate.z });
	mParticle->SetParticleScale({ 1.0f,1.0f,1.0f });*/
	mTransform.UpdateMatrix();
}

void Star::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	if (!mIsPlayerHit) {
		mModel->Draw(commandList, mTransform);
	}
}

void Star::DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
}
