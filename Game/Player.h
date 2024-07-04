#pragma once
#include "GameObject.h"

class Player : public GameObject{
public:
	Player(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	void ParticleDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>, Camera* camera);

	/// <summary>
	/// アクセッサ
	/// </summary>
	int GetHp() { return mHp; }
	bool GetIsEnemyHit() { return mIsEnemyHit; }
	bool GetIsAttack() { return mIsAttack; }
	AABB GetAABB() { return mAABBtranslate; }
	Vector3 GetVelocity() { return mVelocity; }
	Vector3 GetWorldPosition() { return Vector3{ mTransform.mMatWorld.m[3][0],mTransform.mMatWorld.m[3][1],mTransform.mMatWorld.m[3][2] }; }
	Matrix4x4 GetWorldMatrix() { return mTransform.mMatWorld; }
	Transform* GetParent() { return mTransform.mParent; }
	uint32_t GetmAttackTimes() { return mAttackTimes; }
	void SetHp(uint32_t hp) { mHp = hp; }
	void SetIsEnemyHit(bool isEnemyHit) { mIsEnemyHit = isEnemyHit; }
	void SetIsOperatable(bool isOperatable) { mIsOperatable = isOperatable; }
	void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
	void SetIsHit(bool isHit) { mIsHit = isHit; }
	void SetVelocityY(float y) { mVelocity.y = y; }
	void SetGravity(float gravity) { mGravity = gravity; }
	void SetAttackTimes(uint32_t attackTImes) { mAttackTimes = attackTImes; }

private:
	AABB CalcAABB();

private:
	bool mIsOperating; //操作できるかどうかを管理するフラグ
	int32_t mHp; //最大2
	uint32_t mInvincibleTimer; //無敵時間(2秒)

	Vector3 mVelocity;
	float mSpeed;
	float mRotateSpeed; //回転スピード
	float mGravity; //重力

	AABB mAABB; //当たり判定用
	bool mIsMapHit; //壁や床に当たったかどうかを管理するフラグ
	bool mIsEnemyHit; //敵と当たったかどうかを管理するフラグ

	uint32_t mAttackCount; //攻撃できる回数
	bool mIsAttack; //攻撃しているかどうかを管理するフラグ
	int32_t mForwardTimer; //前進タイマー
	int32_t mBackTimer; //後退タイマー

	Matrix4x4 mTransposeViewMatrix;

	//std::vector<std::unique_ptr<Sprite>> mSeedSprite;
	//std::vector<std::unique_ptr<Sprite>> mHeartSprite;
	//std::unique_ptr<ParticleList> mSandSmokeParticle;
};

