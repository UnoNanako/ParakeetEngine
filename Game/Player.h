#pragma once
#include "GameObject.h"
#include <vector>

class PlayerCamera;
class Sprite;
class ParticleManager;

class Player : public GameObject{
public:
	Player(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	/// <summary>
	/// アクセッサ
	/// </summary>
	int GetHp() { return mHp; }
	bool GetIsEnemyHit() { return mIsEnemyHit; }
	bool GetIsAttack() { return mIsAttack; }
	AABB GetAABB() { return mWorldAABB; }
	Vector3 GetVelocity() { return mVelocity; }
	Vector3 GetWorldPosition() { return Vector3{ mTransform.mMatWorld.m[3][0],mTransform.mMatWorld.m[3][1],mTransform.mMatWorld.m[3][2] }; }
	Matrix4x4 GetWorldMatrix() { return mTransform.mMatWorld; }
	uint32_t GetAttackCount() { return mAttackCount; }
	void SetHp(uint32_t hp) { mHp = hp; }
	void SetIsEnemyHit(bool isEnemyHit) { mIsEnemyHit = isEnemyHit; }
	void SetIsOperatable(bool isOperating) { mIsOperating= isOperating; }
	void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
	void SetIsGround(bool isMapHit) { ｍIsGround = isMapHit; }
	void SetVelocityY(float y) { mVelocity.y = y; }
	void SetGravity(float gravity) { mGravity = gravity; }
	void SetAttackCount(uint32_t attackCount) { mAttackCount = attackCount; }
	void SetCamera(std::shared_ptr<PlayerCamera> camera) { mCamera = camera; }

private:
	AABB mLocalAABB; //ローカル
	AABB mWorldAABB; //ワールド
	std::shared_ptr<Model> mModel;
	std::shared_ptr<ParticleManager> mSandSmokeParticle;
	std::shared_ptr<PlayerCamera> mCamera;
	bool mIsOperating; //操作できるかどうかを管理するフラグ
	int32_t mHp; //最大2
	uint32_t mInvincibleTimer = 120; //無敵時間(2秒)

	Vector3 mVelocity;
	float mSpeed;
	float mRotateSpeed; //回転スピード
	float mGravity; //重力
	float mTheta; //角度
	bool ｍIsGround; //壁や床に当たったかどうかを管理するフラグ
	bool mIsEnemyHit; //敵と当たったかどうかを管理するフラグ

	uint32_t mAttackCount; //攻撃できる回数
	bool mIsAttack; //攻撃しているかどうかを管理するフラグ
	int32_t mForwardTimer; //前進タイマー
	int32_t mBackTimer; //後退タイマー

	std::vector<std::shared_ptr<Sprite>> mSeedSprite;
	std::vector<std::shared_ptr<Sprite>> mHeartSprite;
	std::vector<Transform> mSeedSpriteTransform;
	std::vector<Transform> mHeartSpriteTransform;
};

