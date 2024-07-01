#include "MyGame.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"
#include "2D/SpriteCommon.h"
#include "2D/Sprite.h"
#include "Transform.h"
#include "ResourceManager.h"

void MyGame::Initialize() {
	Framework::Initialize();
	auto texture = mResourceManager->Load(mDxCommon, "Resources/sekisei.png");
	mSprite = std::make_shared<Sprite>();
	mSprite->Create(mDxCommon, texture);
	mSpriteTransform.Create(mDxCommon);
	mSpriteTransform.translate = { 100.0f,0.0f,0.0f };
}

void MyGame::Finalize() {
	Framework::Finalize();
}

void MyGame::Update() {
	Framework::Update();

	if (mInput->PushKey(DIK_ESCAPE)) {
		mEndRequest = true;
	}

	mSprite->Update();
	mSpriteTransform.UpdateMatrix();
}

void MyGame::Draw() {
	mImGui->End();
	mDxCommon->PreDraw(); //描画前コマンド

	mSpriteCommon->PreDraw(mDxCommon);
	//-----スプライトの描画ここから-----

	mSprite->Draw(mDxCommon->GetCommandList(),mSpriteTransform);

	//-----スプライトの描画ここまで-----
	mSpriteCommon->PostDraw(mDxCommon);

	mImGui->Draw(mDxCommon);
	mDxCommon->PostDraw(); //描画後コマンド
}
