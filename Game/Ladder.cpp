#include "Ladder.h"
#include "GameObject.h"
#include "3D/Model.h"
#include "2D/Texture.h"
#include "3D/VertexData.h"
#include "MyGame.h"
#include "ResourceManager.h"

Ladder::Ladder(MyGame* myGame)
	:GameObject(myGame) {
}

void Ladder::Initialize() {
	mTransform.mScale = { 1.0f,1.0f,1.0f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform2.mScale = { 1.0f,1.0f,1.0f };
	mTransform2.mRotate = { 0.0f,0.0f,0.0f };
	mTransform2.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform3.mScale = { 1.0f,1.0f,1.0f };
	mTransform3.mRotate = { 0.0f,0.0f,0.0f };
	mTransform3.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mTransform2.Create(mMyGame->GetDxCommon());
	mTransform3.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Ladder/Ladder.gltf");
}

void Ladder::Update() {
	mLocalAABB.mMin = { -0.25f,0.0f,-0.01f };
	mLocalAABB.mMax = { 0.25f,static_cast<float>(mHeight),0.01f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	mTransform.UpdateMatrix();
}

void Ladder::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mModel->Draw(commandList, mTransform);
	if (mHeight >= 2) {
		mTransform2.mTranslate.x = mTransform.mTranslate.x;
		mTransform2.mTranslate.y = mTransform.mTranslate.y + 1.0f;
		mTransform2.mTranslate.z = mTransform.mTranslate.z;
		mTransform2.mRotate = mTransform.mRotate;
		mTransform2.UpdateMatrix();
		mModel->Draw(commandList, mTransform2);
	}
	if (mHeight >= 3) {
		mTransform3.mTranslate.x = mTransform.mTranslate.x;
		mTransform3.mTranslate.y = mTransform.mTranslate.y + 2.0f;
		mTransform3.mTranslate.z = mTransform.mTranslate.z;
		mTransform3.mRotate = mTransform.mRotate;
		mTransform3.UpdateMatrix();
		mModel->Draw(commandList, mTransform3);
	}
}

void Ladder::SetDirection(Direction direction) {
	switch (direction) {
	case Ladder::FRONT:
		mVec = { 0.0f,0.0f,1.0f };
		break;
	case Ladder::BACK:
		mVec = { 0.0f,0.0f,-1.0f };
		break;
	case Ladder::LEFT:
		mVec = { 1.0f,0.0f,0.0f };
		break;
	case Ladder::RIGHT:
		mVec = { -1.0f,0.0f,0.0f };
		break;
	}
}

