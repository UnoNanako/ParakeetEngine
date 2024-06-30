#include "Framework.h"
#include "WinApp.h"
#include "DirectXCommon.h"

void Framework::Initialize() {
	mWinApp = std::make_shared<WinApp>();
	mWinApp->Initialize();
	mDxCommon = std::make_shared<DirectXCommon>();
	mDxCommon->Initialize(mWinApp);
}

void Framework::Finalize() {
	mWinApp->Finalize();
	mDxCommon->Finalize();
}

void Framework::Update() {
}

void Framework::Run() {
	//ゲームの初期化
	Initialize();

	while (true) { //ゲームループ
		//毎フレーム更新
		Update();
		//終了リクエストが来たら抜ける
		if (IsEndRequest()) {
			break;
		}
		//描画
		Draw();
	}
	//ゲーム終了
	Finalize();
}
