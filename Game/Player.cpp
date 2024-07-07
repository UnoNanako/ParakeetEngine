#include "Player.h"
#include "Transform.h"
#include "3D/Model.h"
#include "2D/Texture.h"
#include "3D/Camera.h"
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
	mTransform.Create(mMyGame->GetDxCommon());
	//初期化
	mTransform.mScale = { 0.25f,0.25f,0.25f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,5.0f,0.0f };
	mVelocity = { 0.1f,0.0f,0.1f };
	mGravity = 0.03f;
	mIsEnemyHit = false;
	mIsAttack = false;
	mIsOperating = true;
	mRotateSpeed = 0.05f;
	mSpeed = 0.05f;
	mHp = 2;
	mForwardTimer = 5;
	mBackTimer = 5;
	mAttackCount = 0;

	mLocalAABB.mMin = { -0.25f,-0.0f,-0.25f };
	mLocalAABB.mMax = { 0.25f,0.25f,0.25f };
	mWorldAABB = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Player/Chick.obj");
	mModel->SetShadeType(ShadeType::PHONG);

	mSandSmokeParticle = std::make_unique<ParticleManager>();
	mSandSmokeParticle->SetInitTranslateMin({ -1.0f,-1.0f,-1.0f });
	mSandSmokeParticle->SetInitTranslateMax({ 1.0f,1.0f,1.0f });
	mSandSmokeParticle->SetInitVelocityMin({ -5.0f,5.0f,-5.0f });
	mSandSmokeParticle->SetInitVelocityMax({ 5.0f,6.0f,5.0f });
	mSandSmokeParticle->SetInitLifeTimeMin(0.5f);
	mSandSmokeParticle->SetInitLifeTimeMax(1.0f);

	/*mSeedSprite.resize(5);
	for (uint32_t i = 0; i < mSeedSprite.size(); ++i) {
		mSeedSprite[i] = std::make_unique<Sprite>();
		mSeedSprite[i]->Create(dxCommon, "resources/Sprite/Ui/Seed/SeedSprite.png");
	}

	mHeartSprite.resize(2);
	for (int32_t i = 0; i < mHeartSprite.size(); ++i) {
		mHeartSprite[i] = std::make_unique<Sprite>();
		mHeartSprite[i]->Create(dxCommon, "resources/Sprite/Ui/Heart/Heart.png");
	}*/

	/*mFireParticle = std::make_unique<ParticleList>();
	mFireParticle->Create(mDxCommon);
	mFireParticle->SetFrequency(0.01f);
	mFireParticle->SetParticleTransform({ {2.0f,2.0f,2.0f},{0.0f,0.0f,0.0f},{0.0f,5.0f,0.0f} });
	mFireParticle->SetVelocityMax({ 1.5f,5.0f,1.5f });
	mFireParticle->SetVelocityMin({ -1.5f,2.0f,-1.5f });
	mFireParticle->SetLifeTimeMax(1.0f);
	mFireParticle->SetLifeTImeMin(0.5f);
	mFireParticle->SetColorMax({ 1.0f,0.0f,0.0f });
	mFireParticle->SetColorMin({ 1.0f,0.0f,0.0f });*/
}

void Player::Update(std::shared_ptr<Input> input) {
	mModel->Update();

	/*for (uint32_t i = 0; i < mAttackCount; ++i) {
		mSeedSprite[i]->SetTranslate({ 64.0f * i,80.0f,0.0f });
		mSeedSprite[i]->Update();
	}
	for (int32_t i = 0; i < mHp; ++i) {
		mHeartSprite[i]->SetTranslate({ 64.0f * i,10.0f,0.0f });
		mHeartSprite[i]->Update();
	}*/

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
		}

		if (lStick.x >= 0.1f && lStick.y >= 0.1f) {
			//パーティクル(砂煙)
			mSandSmokeParticle->Update(mMyGame->GetCamera());
			mSandSmokeParticle->SetEmitTranslate({ mTransform.mTranslate.x,mTransform.mTranslate.y,mTransform.mTranslate.z });
			mSandSmokeParticle->SetInitVelocityMax({ 1.0f,4.0f,0.0f });
			mSandSmokeParticle->SetInitVelocityMin({ 0.1f,4.0f,-1.0f });
			mSandSmokeParticle->SetInitLifeTimeMax(0.5f);
			mSandSmokeParticle->SetInitLifeTimeMin(0.2f);
			mSandSmokeParticle->SetInitColorMax({ 116.0f / 255.0f,80.0f / 255.0f,48.0f / 255.0f });
			mSandSmokeParticle->SetInitColorMin({ 116.0f / 255.0f,80.0f / 255.0f,48.0f / 255.0f });
		}


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
			frontVec = { 0.0f,0.0f,1.0f };
			frontVec = Multiply(frontVec, MakeRotateYMatrix(mTransform.mRotate.y));
			mTransform.mTranslate += frontVec;
		} else if (mIsAttack == true && mForwardTimer <= 0) {
			Vector3 frontVec;
			frontVec = { 0.0f,0.0f,1.0f };
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

	//#ifdef _DEBUG
	//	ImGui::Begin("Debug");
	//	ImGui::DragFloat3("player Position", &mTransform.mTranslate.x, 0.01f);
	//	ImGui::DragFloat3("player Rotation", &mTransform.mRotate.x, 0.01f);
	//	ImGui::End();
	//#endif // DEBUG

		//mFireParticle->DrawImGui();

		/*if (mAttackTimes > 0) {
			mFireParticle->Update();
			mFireParticle->SetEmitTransform({ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{mTransform.translate.x,mTransform.translate.y,mTransform.translate.z} });
		}*/
}

void Player::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if ((mInvincibleTimer / 5) % 2 == 0) {
		mModel->Draw(commandList, mTransform);
	}
}

void Player::DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	/*for (uint32_t i = 0; i < mAttackCount; ++i) {
		mSeedSprite[i]->Draw(commandList);
	}
	for (int32_t i = 0; i < mHp; ++i) {
		mHeartSprite[i]->Draw(commandList);
	}*/
}

void Player::ParticleDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mSandSmokeParticle->Draw(commandList);
}
