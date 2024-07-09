#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <vector>
#include <memory>
#include <chrono>

class Player;

class RotateEnemy : public GameObject{
public:
	RotateEnemy(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	bool DetectPlayer(); //プレイヤーが視野角内に収まっているか判定する関数
	void TrackPlayer();
	void Rotate();
	void Chase();
	void Return();

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsAlive() { return mIsAlive; }
	void SetPlayer(std::shared_ptr<Player> player) { mPlayer = player; }
	void SetIsAlive(bool isAlive) { mIsAlive = isAlive; }
	void SetInitTranslate(Vector3 initTranslate) { mInitTranslate = initTranslate; }

private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Model> mModel;
	AABB mLocalAABB;
	AABB mWorldAABB;
	uint32_t mRotateTimer;
	bool mIsRotate;
	float mMoveSpeed;
	float mFovAngle; //視野角
	float mLength; //視線の長さ
	bool mIsPlayerInView; //プレイヤーが視野内にいるか
	bool mIsAlive; //生きているか
	std::chrono::steady_clock::time_point mLastRotationTime; //最後の回転時間
	Vector3 mInitTranslate; //初期位置

	enum State {
		ROTATE, //回転
		CHASE, //追う
		RETURN //戻る
	};
	State mState; //状態
};

