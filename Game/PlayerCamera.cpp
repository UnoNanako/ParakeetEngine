#include "PlayerCamera.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Math/MyMath.h"
#include "Input/Input.h"
#include "Player.h"
#include <algorithm>

PlayerCamera::PlayerCamera() {
	mOffset = { 0.0f,0.0f,-10.0f };
	mRotate.x = kPi / 180.0f * 30.0f;
	mActualRotate = mRotate;
	//mT = 0.0f;
}

void PlayerCamera::Update(std::shared_ptr<Input> input) {
	if (!mIsFixed) {
		//ゲームパッドの右スティックの入力を取得
		Vector2 rStick = input->GetRStick();
		if (Length(rStick) >= 0.5f) {
			//カメラの方位角と仰角を更新
			mActualRotate.y += rStick.x * 0.02f;
			mActualRotate.x -= rStick.y * 0.02f;
			mActualRotate.x = Max((kPi / 180.0f * 20.0f), Min(mActualRotate.x, static_cast<float>(kPi / 2)));
		}
	}
	if (input->GetButtonDown(XINPUT_GAMEPAD_X)) {
		mActualRotate.y = mPlayer->GetRotate().y;
		mActualRotate.x = kPi / 180.0f * 30.0f;
	}

	float t = 0.2f;
	mRotate.x = std::lerp(mRotate.x, mActualRotate.x, t);
	mRotate.y = std::lerp(mRotate.y, mActualRotate.y, t);
	mRotate.z = std::lerp(mRotate.z, mActualRotate.z, t);

	Matrix4x4 rotateMatrix = MakeRotateMatrix(mRotate);
	Vector3 offset = Multiply(mOffset, rotateMatrix);
	mTranslate = mPlayer->GetTranslate() + offset;

	//線形補間
	/*if (!isTitleScene) {
		mT += 0.05f;
		if (mT > 1.0f) {
			mT = 1.0f;
		}
		float x = mRadius * sin(mLat) * cos(mLon) + playerTranslate.x;
		float y = mRadius * cos(mLat) + playerTranslate.y;
		float z = mRadius * sin(mLat) * sin(mLon) + playerTranslate.z;
		Vector3 tmp = { x - mStartPos.x,y - mStartPos.y,z - mStartPos.z };
		tmp.x = mStartPos.x + (x - mStartPos.x) * mT;
		tmp.y = mStartPos.y + (y - mStartPos.y) * mT;
		tmp.z = mStartPos.z + (z - mStartPos.z) * mT;
		mTransform.translate.x = tmp.x;
		mTransform.translate.y = tmp.y;
		mTransform.translate.z = tmp.z;
	}*/

	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, mRotate, mTranslate);
	mViewMatrix = Inverse(worldMatrix);
	mProjectionMatrix = MakePerspectiveFovMatrix(50.0f * (kPi / 180.0f), WinApp::kClientWidth / float(WinApp::kClientHeight), 0.1f, 1000.0f);
}