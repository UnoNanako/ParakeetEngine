#include "Input.h"
#include "WinApp.h"
#include <cassert>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "xinput.lib")

void Input::Initialize(std::shared_ptr<WinApp> winApp){
	//借りてきたWinApiManagerのインスタンスを記録
	mWinApp = winApp;
	HRESULT hr;
	hr = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&mDirectInput, nullptr);
	assert(SUCCEEDED(hr));
	hr = mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);
	assert(SUCCEEDED(hr));
	//入力データ形式のセット
	hr = mKeyboard->SetDataFormat(&c_dfDIKeyboard); //標準形式
	assert(SUCCEEDED(hr));
	//排他制御レベルのセット
	hr = mKeyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));
}

void Input::Update(){
	memcpy(mPreKeys, mKeys, sizeof(mKeys));
	//キーボード情報の取得開始
	mKeyboard->Acquire();
	mKeyboard->GetDeviceState(sizeof(mKeys), mKeys);

	//ゲームパッド
	mPrev = mCurr;
	XInputGetState(0, &mCurr);
}

bool Input::PushKey(BYTE keyNumber) {
	//0で無ければ押している
	if (mKeys[keyNumber]) {
		return true;
	}
	//押していない
	return false;
}

//キーがトリガーか関数
bool Input::TriggerKey(BYTE keyNumber) {
	//前回が0で今回が0出なければトリガー
	if (!mPreKeys[keyNumber] && mKeys[keyNumber]) {
		return true;
	}
	//トリガーではない
	return false;
}

bool Input::GetButton(int button){
	return mCurr.Gamepad.wButtons & button;
}

bool Input::GetButtonUp(int button){
	return !(mCurr.Gamepad.wButtons & button) && mPrev.Gamepad.wButtons & button;
}

bool Input::GetButtonDown(int button){
	return mCurr.Gamepad.wButtons & button && !(mPrev.Gamepad.wButtons & button);
}

Vector2 Input::GetLStick(){
	return Vector2(
		mCurr.Gamepad.sThumbLX / 32768.0f,
		mCurr.Gamepad.sThumbLY / 32768.0f);
}

Vector2 Input::GetRStick(){
	return Vector2(
		mCurr.Gamepad.sThumbRX / 32768.0f,
		mCurr.Gamepad.sThumbRY / 32768.0f);
}

float Input::GetLTrigger(){
	return mCurr.Gamepad.bLeftTrigger / 255.0f;
}

float Input::GetRTrigger(){
	return mCurr.Gamepad.bRightTrigger / 255.0f;
}
