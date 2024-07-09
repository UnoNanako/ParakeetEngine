#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class Player;

class Ghost : public GameObject{
public:
	Ghost(MyGame* mMyGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	bool DetectPlayer(); //プレイヤーが視野角内に収まっているか判定する関数
	void TrackPlayer();

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	void SetPlayer(std::shared_ptr<Player> player) { mPlayer = player; }
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Model> mModel;
	AABB mLocalAABB;
	AABB mWorldAABB;
	float mFovAngle; //視野角
	float mLength; //視線の長さ
	bool mIsPlayerInView; //プレイヤーが視野内にいるか
	Vector3 mVelocity;
	enum Direction {
		LEFT,
		RIGHT
	};
	Direction mDirection; //向き
};

