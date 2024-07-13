#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class ParticleManager;
class Sprite;

class Gem : public GameObject{
public:
	Gem(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	
	/// <summary>
	/// アクセッサ
	/// </summary>
	AABB GetWorldAABB() { return mWorldAABB; }
	bool GetIsHit() { return mIsPlayerHit; }
	void SetTranslate(Vector3 translate) { mTransform.mTranslate = translate; }
	void SetSpriteTranslate(Vector3 translate) { mSpriteTransform.mTranslate = translate; }
	void SetIsHit(bool isHit) { mIsPlayerHit = isHit; }

private:
	std::shared_ptr<Model> mModel;
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<ParticleManager> mParticle;
	std::shared_ptr<Sprite> mGemSprite;
	std::shared_ptr<Sprite> mNotGemSprite;
	Transform mSpriteTransform;
	bool mIsPlayerHit;
};

