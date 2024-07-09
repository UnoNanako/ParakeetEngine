#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class Seed : public GameObject{
public:
	Seed(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;

	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsHit() { return mIsHit; }
	void SetTranslate(Vector3 translate) { mTransform.mTranslate = translate; }
	void SetIsHit(bool isHit) { mIsHit = isHit; }

private:
	std::shared_ptr<Model> mModel;
	AABB mLocalAABB;
	AABB mWorldAABB;
	bool mIsHit = false;
};

