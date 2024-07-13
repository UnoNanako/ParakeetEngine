#pragma once
#include "3D/Camera.h"
#include <wrl.h>
#include <d3d12.h>
#include <memory>

class DirectXCommon;
class Player;
class MyMath;
class Input;

class PlayerCamera : public Camera{
public:
	PlayerCamera();
	void Update(std::shared_ptr<Input> input)override;

	/// <summary>
	/// アクセッサ
	/// </summary>
	Matrix4x4 GetViewMatrix() { return mViewMatrix; }
	void SetPlayer(std::shared_ptr<Player> player) { mPlayer = player; }
	void SetIsFixed(bool isFixed) { mIsFixed = isFixed; }
	void SetIsTitleScene(bool isTitleScene) { mIsTitleScene = isTitleScene; }

private:
	std::shared_ptr<Player> mPlayer;
	Vector3 mOffset;
	Vector3 mActualRotate;
	bool mIsFixed = false; //カメラを固定しているかどうか
	bool mIsTitleScene; //タイトル画面かどうか
	//float mT; //線形補間
	//Vector3 mStartPos; //線形補間開始位置
};

