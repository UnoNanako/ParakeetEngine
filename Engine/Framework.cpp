#include "Framework.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"
#include "2D/SpriteCommon.h"

void Framework::Initialize() {
	mWinApp = std::make_shared<WinApp>();
	mWinApp->Initialize();
	mDxCommon = std::make_shared<DirectXCommon>();
	mDxCommon->Initialize(mWinApp);
	mInput = std::make_shared<Input>();
	mInput->Initialize(mWinApp);
	mImGui = std::make_shared<ImGuiManager>();
	mImGui->Initialize(mWinApp,mDxCommon);
	mSpriteCommon = std::make_shared<SpriteCommon>();
	mSpriteCommon->Initialize(mDxCommon);
}

void Framework::Finalize() {
	mSpriteCommon->Finalize();
	mImGui->Finalize();
	mDxCommon->Finalize();
	mWinApp->Finalize();
}

void Framework::Update() {
	mImGui->Begin();
	mInput->Update();
}

void Framework::Run() {
	//ゲームの初期化
	Initialize();

	MSG msg{};
	while (msg.message != WM_QUIT) {
		//Windoeにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			//毎フレーム更新
			Update();
			//終了リクエストが来たら抜ける
			if (mEndRequest) {
				break;
			}
			//描画
			Draw();
		}
	}
	//ゲーム終了
	Finalize();
}
