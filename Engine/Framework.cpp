#include "Framework.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input/Input.h"
#include "ImGuiManager.h"
#include "2D/SpriteCommon.h"
#include "ResourceManager.h"
#include "3D/ModelCommon.h"
#include "3D/Camera.h"
#include "3D/ParticleCommon.h"

void Framework::Initialize() {
	mWinApp = std::make_shared<WinApp>();
	mWinApp->Initialize();
	mDxCommon = std::make_shared<DirectXCommon>();
	mDxCommon->Initialize(mWinApp);
	mInput = std::make_shared<Input>();
	mInput->Initialize(mWinApp);
	mImGui = std::make_shared<ImGuiManager>();
	mImGui->Initialize(mWinApp,mDxCommon);
	mResourceManager = std::make_shared<ResourceManager>();
	mResourceManager->Initialize(mDxCommon);
	mSpriteCommon = std::make_shared<SpriteCommon>();
	mSpriteCommon->Initialize(mDxCommon);
	mModelCommon = std::make_shared<ModelCommon>();
	mModelCommon->Initialize(mDxCommon);
	mParticleCommon = std::make_shared<ParticleCommon>();
	mParticleCommon->Initialize(mDxCommon);
}

void Framework::Finalize() {
	mParticleCommon->Finalize();
	mModelCommon->Finalize();
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
