#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class ParticleList;
class Sprite;

class Star : public GameObject{
public:
	Star(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	/// <summary>
	/// アクセッサ
	/// </summary>
	void SetTranslate(Vector3 translate) { mTransform.mTranslate = translate; }
	void SetIsPlayerHit(bool isHit) { mIsPlayerHit = isHit; }
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsPlayerHit() { return mIsPlayerHit; }

private:
	std::shared_ptr<Model> mModel;
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<ParticleList> mParticle;
	bool mIsPlayerHit;
};

