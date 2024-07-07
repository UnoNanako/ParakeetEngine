#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <wrl.h>

class Ladder : public GameObject{
public:
	enum Direction {
		FRONT,
		BACK,
		LEFT,
		RIGHT
	};
	Ladder(MyGame* myGame);
	void Initialize()override;
	void Update();
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsHitPlayer() { return mIsHit; }
	Vector3 GetVec() { return mVec; }
	Direction GetDirection() { return mDirection; }
	uint32_t GetHeight() { return mHeight; }
	void SetIsHitPlayer(bool isHit) { mIsHit = isHit; }
	void SetVec(Vector3 vec) { mVec = vec; }
	void SetDirection(Direction direction);
	void SetHeight(uint32_t height) { mHeight = height; }

private:
	Transform mTransform2;
	Transform mTransform3;
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<Model> mModel;
	bool mIsHit = false;
	Vector3 mVec;
	Direction mDirection;
	uint32_t mHeight;
};

