#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <vector>
#include <memory>

class WalkEnemy : public GameObject{
public:
	WalkEnemy(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsAlive() { return mIsAlive; }
	void SetIsAlive(bool isAlive) { mIsAlive = isAlive; }
	void SetMoveMax(Vector3 moveMax) { mMoveMax = moveMax; }
	void SetMoveMin(Vector3 moveMin) { mMoveMin = moveMin; }

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	void SetDirection(Direction direction) { mDirection = direction; }

private:
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<Model> mModel;
	Vector3 mVelocity;
	Vector3 mMoveMax; //移動範囲の最大
	Vector3 mMoveMin; //移動範囲の最小
	bool mIsAlive; //生きているか
	Direction mDirection = DOWN; //向き
};

