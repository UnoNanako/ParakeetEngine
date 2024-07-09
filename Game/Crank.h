#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <vector>
#include <memory>

class Sprite;

class Crank : public GameObject{
public:
	Crank(MyGame* myGame);
	void Initialize();
	void Update(std::shared_ptr<Input> input);
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsHit() { return mIsHit; }
	void SetIsHit(bool isHit) { mIsHit = isHit; }
	bool GetIsPushA() { return mIsPushA; }
	void SetIsPushA(bool isPushA) { mIsPushA = isPushA; }

private:
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<Model> mCrankModel; //クランク本体
	std::shared_ptr<Model> mFoundationModel; //土台
	Transform mFoundationTransform; //土台
	std::shared_ptr<Sprite> mRStickSprite;
	Transform mRStickTransform; //RスティックのUIのポジション
	float mCalculateAngle; //前の角度
	float mCurrentAngle; //現在の角度
	bool mIsHit = false; //プレイヤーと当たっているか
	bool mIsPushA = false; //Aボタンが押されたか
};

