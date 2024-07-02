#include "MyGame.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"
#include "2D/SpriteCommon.h"
#include "2D/Sprite.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "3D/ModelCommon.h"
#include "3D/Camera.h"
#include "3D/Model.h"

void MyGame::Initialize() {
	Framework::Initialize();
	auto texture = mResourceManager->LoadTexture(mDxCommon, "Resources/Sekisei.png");
	mSprite = std::make_shared<Sprite>();
	mSprite->Create(mDxCommon, texture);
	mSpriteTransform.Create(mDxCommon);
	mSpriteTransform.mTranslate = { 100.0f,0.0f,0.0f };

	mModel = mResourceManager->LoadModel(mDxCommon, "Resources/Models/Player/Chick.obj");
	mModelTransform.Create(mDxCommon);
	mModelTransform.mTranslate = { 0.0f,0.0f,10.0f };

	mCamera = std::make_shared<Camera>();
	mCamera->Initialize(mDxCommon);
}

void MyGame::Finalize() {
	Framework::Finalize();
}

void MyGame::Update() {
	Framework::Update();

	if (mInput->PushKey(DIK_ESCAPE)) {
		mEndRequest = true;
	}
	mSpriteTransform.UpdateMatrix();
	mModelTransform.UpdateMatrix();
	mCamera->UpdateMatrix();
}

void MyGame::Draw() {
	mImGui->End();
	mDxCommon->PreDraw(); //描画前コマンド

	mModelCommon->PreDraw(mDxCommon,mCamera);
	//-----モデルの描画ここから-----
	mModel->Draw(mDxCommon->GetCommandList(), mModelTransform);
	//-----モデルの描画ここまで-----
	mModelCommon->PostDraw(mDxCommon);

	mSpriteCommon->PreDraw(mDxCommon);
	//-----スプライトの描画ここから-----
	mSprite->Draw(mDxCommon->GetCommandList(),mSpriteTransform);
	//-----スプライトの描画ここまで-----
	mSpriteCommon->PostDraw(mDxCommon);

	mImGui->Draw(mDxCommon);
	mDxCommon->PostDraw(); //描画後コマンド
}
