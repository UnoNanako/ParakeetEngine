#include "Player.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/Camera.h"
#include "3D/ParticleManager.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "PlayerCamera.h"
#include "MyGame.h"
#include "ResourceManager.h"
#include "Math/MyMath.h"
#include "Input/Input.h"
#include "externals/imgui/imgui.h"
#include <format>

Player::Player(MyGame* myGame)
	:GameObject(myGame) {
}

void Player::Initialize() {
	mTransform.mScale = { 0.25f,0.25f,0.25f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { -5.0f,5.0f,-4.5f };
	mTransform.Create(mMyGame->GetDxCommon());
	mVelocity = { 0.1f,0.0f,0.1f };
	mGravity = 0.03f;
	mIsEnemyHit = false;
	mIsAttack = false;
	mIsOperating = true;
	mRotateSpeed = 0.05f;
	mSpeed = 0.05f;
	mHp = 3;
	mForwardTimer = 5;
	mBackTimer = 5;
	mAttackCount = 0;

	mLocalAABB.mMin = { -0.25f,-0.0f,-0.25f };
	mLocalAABB.mMax = { 0.25f,0.25f,0.25f };
	mWorldAABB = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Player/Chick.obj");
	mModel->SetShadeType(ShadeType::PHONG);

	mSandSmokeParticle = std::make_shared<ParticleManager>();
	mSandSmokeParticle->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Particle/SandSmoke.png"));
	mSandSmokeParticle->SetInitTranslateMin({ -0.0f,-0.0f,-0.0f });
	mSandSmokeParticle->SetInitTranslateMax({ 0.0f,0.0f,0.0f });
	mSandSmokeParticle->SetInitVelocityMin({ -0.3f,0.3f,-0.3f });
	mSandSmokeParticle->SetInitVelocityMax({ 0.3f,0.5f,0.3f });
	mSandSmokeParticle->SetInitLifeTimeMin(0.2f);
	mSandSmokeParticle->SetInitLifeTimeMax(0.5f);
	mSandSmokeParticle->SetInitColorMax({ 116.0f / 255.0f,80.0f / 255.0f,48.0f / 255.0f });
	mSandSmokeParticle->SetInitColorMin({ 116.0f / 255.0f,80.0f / 255.0f,48.0f / 255.0f });
	mSandSmokeParticle->SetInitScale({ 0.3f,0.3f,0.3f });

	mSeedSprite.resize(5);
	mSeedSpriteTransform.resize(5);
	for (uint32_t i = 0; i < mSeedSprite.size(); ++i) {
		mSeedSprite[i] = std::make_shared<Sprite>();
		mSeedSprite[i]->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/Ui/Seed/Seed.png"));
		mSeedSpriteTransform[i].mScale = { 1.0f,1.0f,1.0f };
		mSeedSpriteTransform[i].mRotate = { 0.0f,0.0f,0.0f };
		mSeedSpriteTransform[i].mTranslate = { 64.0f,0.0f,0.0f };
		mSeedSpriteTransform[i].Create(mMyGame->GetDxCommon());
	}
	mHeartSprite.resize(3);
	mHeartSpriteTransform.resize(3);
	for (int32_t i = 0; i < mHeartSprite.size(); ++i) {
		mHeartSprite[i] = std::make_shared<Sprite>();
		mHeartSprite[i]->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/Ui/Heart/Heart.png"));
		mHeartSpriteTransform[i].mScale = { 1.0f,1.0f,1.0f };
		mHeartSpriteTransform[i].mRotate = { 0.0f,0.0f,0.0f };
		mHeartSpriteTransform[i].mTranslate = { 64.0f,0.0f,0.0f };
		mHeartSpriteTransform[i].Create(mMyGame->GetDxCommon());
	}
}

void Player::Update(std::shared_ptr<Input> input) {
	mModel->Update();
	//Lスティック
	Vector2 lStick = input->GetLStick();
	//Rスティック
	Vector2 rStick = input->GetRStick();
	//回転行列
	Matrix4x4 rotationMatrix = MakeRotateYMatrix(mCamera->GetRotate().y);
	Vector3 frontVec = { 0.0f,0.0f,1.0f };//前方
	Vector3 rightVec = { 1.0f,0.0f,0.0f };//右方向
	//2つのベクトルをそれぞれビュー行列で変換。ビューに対して前方と右方向のベクトルが求まる
	frontVec = Multiply(frontVec, rotationMatrix);
	rightVec = Multiply(rightVec, rotationMatrix);
	//ここまで

	if (mIsOperating) {
		//ゲームパッド
		if (Length(lStick) >= 0.5f) {
			frontVec *= lStick.y;
			rightVec *= lStick.x;
			mTransform.mTranslate += frontVec * mSpeed;
			mTransform.mTranslate += rightVec * mSpeed;
			//カメラの回転 + スティックの方向 + 90°
			mTransform.mRotate.y = mCamera->GetRotate().y + atan2f(-lStick.y, lStick.x) + kPi / 2.0f;
			mSandSmokeParticle->SetIsPlaying(true);
		} else {
			mSandSmokeParticle->SetIsPlaying(false);
		}
		//パーティクル
		mSandSmokeParticle->Update(mMyGame->GetCamera());
		mSandSmokeParticle->SetEmitTranslate({ mTransform.mTranslate.x,mTransform.mTranslate.y,mTransform.mTranslate.z });
		//Bボタン
		if (input->GetButtonDown(XINPUT_GAMEPAD_B)) {
			if (mAttackCount > 0) {
				mIsAttack = true;
				--mAttackCount;
			}
		}
		if (mIsAttack == true && mForwardTimer > 0) {
			--mForwardTimer;
			Vector3 frontVec;
			frontVec = { 0.0f,0.0f,0.5f };
			frontVec = Multiply(frontVec, MakeRotateYMatrix(mTransform.mRotate.y));
			mTransform.mTranslate += frontVec;
		} else if (mIsAttack == true && mForwardTimer <= 0) {
			Vector3 frontVec;
			frontVec = { 0.0f,0.0f,0.5f };
			frontVec = Multiply(frontVec, MakeRotateYMatrix(mTransform.mRotate.y));
			mTransform.mTranslate -= frontVec;
			--mBackTimer;
			if (mBackTimer <= 0) {
				mIsAttack = false;
				mForwardTimer = 5;
				mBackTimer = 5;
			}
		}
	}

	mVelocity.y -= mGravity; //毎フレーム重力をかけている
	if (ｍIsGround) { //地面に当たったら
		mVelocity.y = 0.0f;
	}
	mTransform.mTranslate.y += mVelocity.y;
	//リスポーン
	if (mTransform.mTranslate.y <= -50.0f) {
		Initialize();
	}

	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);

	//敵と当たっているとき
	if (mIsEnemyHit == true) {
		--mInvincibleTimer;
		if (mInvincibleTimer <= 0) {
			mIsEnemyHit = false;
			mInvincibleTimer = 120;
		}
	}

	for (uint32_t i = 0; i < mSeedSprite.size(); ++i) {
		mSeedSpriteTransform[i].mTranslate = { i * 64.0f,80.0f,0.0f };
		mSeedSpriteTransform[i].UpdateMatrix();
	}
	for (uint32_t i = 0; i < mHeartSprite.size(); ++i) {
		mHeartSpriteTransform[i].mTranslate = { i * 64.0f,10.0f,0.0f };
		mHeartSpriteTransform[i].UpdateMatrix();
	}
}

void Player::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if ((mInvincibleTimer / 5) % 2 == 0) {
		mModel->Draw(commandList, mTransform);
	}
}

void Player::DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	for (uint32_t i = 0; i < mAttackCount; ++i) {
		mSeedSprite[i]->Draw(commandList, mSeedSpriteTransform[i]);
	}
	for (int32_t i = 0; i < mHp; ++i) {
		mHeartSprite[i]->Draw(commandList, mHeartSpriteTransform[i]);
	}
}

void Player::DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mSandSmokeParticle->Draw(commandList);
}
