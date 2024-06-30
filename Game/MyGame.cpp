#include "MyGame.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"

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
	mDxCommon->PreDraw(); //描画前コマンド
	mImGui->End();
	mImGui->Draw(mDxCommon);
	mDxCommon->PostDraw(); //描画後コマンド
}
