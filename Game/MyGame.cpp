#include "MyGame.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"
#include "2D/SpriteCommon.h"

void MyGame::Initialize() {
	Framework::Initialize();
}

void MyGame::Finalize() {
	Framework::Finalize();
}

void MyGame::Update() {
	Framework::Update();

	if (mInput->PushKey(DIK_ESCAPE)) {
		mEndRequest = true;
	}
}

void MyGame::Draw() {
	mImGui->End();
	mDxCommon->PreDraw(); //描画前コマンド

	mSpriteCommon->PreDraw(mDxCommon);
	//-----スプライトの描画ここから-----

	//-----スプライトの描画ここまで-----
	mSpriteCommon->PostDraw(mDxCommon);

	mImGui->Draw(mDxCommon);
	mDxCommon->PostDraw(); //描画後コマンド
}
