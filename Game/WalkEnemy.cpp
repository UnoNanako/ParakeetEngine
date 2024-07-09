#include "WalkEnemy.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"

WalkEnemy::WalkEnemy(MyGame* myGame)
	:GameObject(myGame){
}

void WalkEnemy::Initialize(){
	mTransform.mScale = { 0.4f,0.4f,0.4f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/WalkEnemy/Goblin.obj");
	mVelocity = { 0.02f,0.0f,0.02f };
	mIsAlive = true;
}

void WalkEnemy::Update(std::shared_ptr<Input> input){
	mLocalAABB.mMin = { -0.4f,-0.4f,-0.4f };
	mLocalAABB.mMax = { 0.4f,0.4f,0.4f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);

	switch (mDirection) {
	case UP:
		mTransform.mRotate = { 0.0f,0.0f,0.0f };
		mTransform.mTranslate.z += mVelocity.z;
		if (mTransform.mTranslate.z > mMoveMax.z) {
			mDirection = RIGHT;
		}
		break;
	case DOWN:
		mTransform.mRotate = { 0.0f,kPi,0.0f };
		mTransform.mTranslate.z -= mVelocity.z;
		if (mTransform.mTranslate.z < mMoveMin.z) {
			mDirection = LEFT;
		}
		break;
	case LEFT:
		mTransform.mRotate = { 0.0f,-kPi / 2.0f,0.0f };
		mTransform.mTranslate.x -= mVelocity.x;
		if (mTransform.mTranslate.x < mMoveMin.x) {
			mDirection = UP;
		}
		break;
	case RIGHT:
		mTransform.mRotate = { 0.0f,kPi / 2.0f,0.0f };
		mTransform.mTranslate.x += mVelocity.x;
		if (mTransform.mTranslate.x > mMoveMax.x) {
			mDirection = DOWN;
		}
		break;
	}
	mTransform.UpdateMatrix();
}

void WalkEnemy::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	if (mIsAlive) {
		mModel->Draw(commandList,mTransform);
	}
}
