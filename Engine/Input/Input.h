#pragma once
#include <windows.h>
#include <Xinput.h>
#include <cstdint>
#define DIRECTINPUT_VERSION	    0x0800 //DirectInputのバージョン指定
#include <dinput.h>
#include <wrl.h>
#include <memory>
#include "MyMath.h"

class WinApp;

//入力
class Input{
public: //メンバ関数
	//キーボード
	//初期化
	void Initialize(std::shared_ptr<WinApp> winApp);
	//更新
	void Update();
	//キーが押されているか関数
	bool PushKey(BYTE keyNumber);
	//キーがトリガーか関数
	bool TriggerKey(BYTE keyNumber);

	//ゲームパッド
	bool GetButton(int button);
	bool GetButtonUp(int button);
	bool GetButtonDown(int button);
	Vector2 GetLStick();
	Vector2 GetRStick();
	float GetLTrigger();
	float GetRTrigger();

private: //メンバ変数
	//WindowsAPI
	std::shared_ptr<WinApp> mWinApp;
	//DirectInputオブジェクトの生成
	Microsoft::WRL::ComPtr<IDirectInput8> mDirectInput = nullptr;
	//キーボードデバイスの生成
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mKeyboard = nullptr;
	//全キーの入力状態を取得する
	BYTE mKeys[256] = {};
	BYTE mPreKeys[256] = {};

	//ゲームパッド
	XINPUT_STATE mCurr;
	XINPUT_STATE mPrev;
};
