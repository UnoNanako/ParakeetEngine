#include "MyGame.h"
#include "DirectXCommon.h"

void MyGame::Initialize() {
	Framework::Initialize();
}

void MyGame::Finalize() {
	Framework::Finalize();
}

void MyGame::Update() {
	Framework::Update();
}

void MyGame::Draw() {
	mDxCommon->PreDraw(); //描画前コマンド

	mDxCommon->PostDraw(); //描画後コマンド
}
