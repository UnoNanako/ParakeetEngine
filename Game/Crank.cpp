#include "Crank.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"

Crank::Crank(MyGame* myGame)
	:GameObject(myGame) {
}

void Crank::Initialize() {
	mCalculateAngle = 0.0f;
	mCurrentAngle = 0.0f;
	mTransform.mScale = { 0.5f,0.5f,0.5f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,3.0f,2.5f };
	mFoundationTransform.mScale = { 0.5f,0.5f,0.5f };
	mFoundationTransform.mRotate = { 0.0f,0.0f,0.0f };
	mFoundationTransform.mTranslate = { 0.0f,3.0f,2.5f };
	mRStickTransform.mScale = { 1.0f,1.0f,1.0f };
	mRStickTransform.mRotate = { 0.0f,0.0f,0.0f };
	mRStickTransform.mTranslate = { 600.0f,500.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mFoundationTransform.Create(mMyGame->GetDxCommon());
	mRStickTransform.Create(mMyGame->GetDxCommon());
	mCrankModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Crank/Crank.obj"); //クランク本体
	mFoundationModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Foundation/Foundation.obj"); //土台
	mRStickSprite = std::make_shared<Sprite>();
	mRStickSprite->Create(mMyGame->GetDxCommon(),mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/Ui/Buttons/xbox_stick_top_r.png"));
}

void Crank::Update(std::shared_ptr<Input> input) {
	mLocalAABB.mMin = { -0.5f,-0.5f,-0.5f };
	mLocalAABB.mMax = { 0.5f,0.5f,0.5f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	//Rスティック
	Vector2 rStick = input->GetRStick();
	float length = Length(rStick);
	if (length > 0.0f && mIsHit == true) {
		rStick.Normalize();
		mCalculateAngle = mCurrentAngle; //前のフレームの角度
		mCurrentAngle = atan2(rStick.y, rStick.x); //ラジアンが求まる
		float angle = mCurrentAngle - mCalculateAngle;
		if (angle > 0.05f) {
			angle = 0.02f;
		}
		if (angle < -0.05f) {
			angle = -0.02f;
		}
		mTransform.mRotate.y -= angle;
	}
	mTransform.UpdateMatrix();
	mFoundationTransform.UpdateMatrix();
	mRStickTransform.UpdateMatrix();
}

void Crank::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mCrankModel->Draw(commandList,mTransform);
	mFoundationModel->Draw(commandList,mFoundationTransform);
}

void Crank::DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	if (mIsHit) {
		mRStickSprite->Draw(commandList, mRStickTransform);
	}
}
