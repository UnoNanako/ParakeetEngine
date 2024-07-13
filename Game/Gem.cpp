#include "Gem.h"
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

Gem::Gem(MyGame* myGame)
	:GameObject(myGame) {
}

void Gem::Initialize() {
	mTransform.mScale = { 0.2f,0.2f,0.2f };
	mTransform.mRotate = { kPi / 2.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Gem/Gem.gltf");
	mGemSprite = std::make_shared<Sprite>();
	mGemSprite->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/Ui/Gem/Diamond.png"));
	mNotGemSprite = std::make_unique<Sprite>();
	mNotGemSprite->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/Ui/Gem/DiamondNone.png"));
	mSpriteTransform.mScale = { 1.0f,1.0f,1.0f };
	mSpriteTransform.mRotate = { 0.0f,0.0f,0.0f };
	mSpriteTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mSpriteTransform.Create(mMyGame->GetDxCommon());

	mParticle = std::make_shared<ParticleManager>();
	mParticle->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Particle/Effect.png"));
	mParticle->SetInitTranslateMin({ -0.1f,-0.1f,-0.1f });
	mParticle->SetInitTranslateMax({ 0.1f,0.1f,0.1f });
	mParticle->SetInitVelocityMin({ -1.0f,1.0f,-1.0f });
	mParticle->SetInitVelocityMax({ 1.0f,1.5f,1.0f });
	mParticle->SetInitColorMin({ 0.0f,0.0f,0.0f });
	mParticle->SetInitColorMax({ 1.0f,1.0f,1.0f });
	mParticle->SetInitLifeTimeMin(0.5f);
	mParticle->SetInitLifeTimeMax(1.0f);
	mParticle->SetInitScale({ 0.15f,0.15f,0.15f });

	mIsPlayerHit = false;
}

void Gem::Update(std::shared_ptr<Input> input) {
	mTransform.mRotate.y += 0.05f;
	mLocalAABB.mMin = { -0.2f,-0.5f,-0.2f };
	mLocalAABB.mMax = { 0.2f,0.2f,0.2f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	if (mIsPlayerHit) {
		mModel->Update();
	}
	mSpriteTransform.UpdateMatrix();
	mTransform.UpdateMatrix();

	mParticle->Update(mMyGame->GetCamera());
	mParticle->SetEmitTranslate({ mTransform.mTranslate.x,mTransform.mTranslate.y,mTransform.mTranslate.z });
}

void Gem::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if (!mIsPlayerHit) {
		mModel->Draw(commandList, mTransform);
	}
}

void Gem::DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if (mIsPlayerHit) {
		mGemSprite->Draw(commandList, mSpriteTransform);
	} else {
		mNotGemSprite->Draw(commandList, mSpriteTransform);
	}
}

void Gem::DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if (!mIsPlayerHit) {
		mParticle->Draw(commandList);
	}
}
