#pragma once
#include <d3d12.h>
#include <string>
#include "Transform.h"
#include "Particle.h"
#include <wrl.h>
#include <random>
#include <numbers>
#include <list>

class DirectXCommon;
struct ParticleForGPU;
class Camera;
class Texture;
struct VertexData;
struct Material;

const uint32_t kMaxInstance = 100; //インスタンス数

class ParticleManager{
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture);
	void Update(std::shared_ptr<Camera> camera);
	void Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	/// <summary>
	/// アクセッサ
	/// </summary>
	bool GetIsPlaying() { return mIsPlaying; }
	void SetIsPlaying(bool isPlaying) { mIsPlaying = isPlaying; }
	//エミッタ
	void SetEmitCount(uint32_t count) { mEmitter.mCount = count; }
	void SetEmitTranslate(Vector3 translate) { mEmitter.mTransform.mTranslate = translate; }
	void SetEmitFrequency(float frequency) { mEmitter.mFrequency = frequency; }
	//パーティクル
	void SetInitTranslateMin(Vector3 translateMin) { mInitTranslateMin = translateMin; }
	void SetInitTranslateMax(Vector3 translateMax) { mInitTranslateMax = translateMax; }
	void SetInitVelocityMin(Vector3 velocityMin) { mInitVelocityMin = velocityMin; }
	void SetInitVelocityMax(Vector3 velocityMax) { mInitVelocityMax = velocityMax; }
	void SetInitColorMin(Vector3 colorMin) { mInitColorMin = colorMin; }
	void SetInitColorMax(Vector3 colorMax) { mInitColorMax = colorMax; }
	void SetInitLifeTImeMin(float lifeTimeMin) { mInitLifeTimeMin = lifeTimeMin; }
	void SetInitLifeTimeMax(float lifeTimeMax) { mInitLifeTimeMax = lifeTimeMax; }

private:
	Particle MakeParticle(const Vector3& translate);
	std::list<Particle> Emit(const Emitter& emitter);

private:
	std::shared_ptr<Texture> mTexture;
	Microsoft::WRL::ComPtr<ID3D12Resource> mInstancingResourse;
	ParticleForGPU* mInstancingData;
	D3D12_GPU_DESCRIPTOR_HANDLE mInstancingSrvHandleGPU;
	Microsoft::WRL::ComPtr<ID3D12Resource> mVertexResource;
	VertexData* mVertexData;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> mMaterialResource;
	Material* mMaterialData;

	uint32_t mNumInstance = 0; //描画すべきインスタンス数
	//Particle mParticles[kMaxInstance];
	std::list<Particle> mParticles;

	bool mIsPlaying; //パーティクルが出ているか
	Emitter mEmitter{};

	//ランダム範囲の最小、最大
	Vector3 mInitTranslateMin;
	Vector3 mInitTranslateMax;
	Vector3 mInitVelocityMin;
	Vector3 mInitVelocityMax;
	Vector3 mInitColorMin;
	Vector3 mInitColorMax;
	float mInitLifeTimeMin;
	float mInitLifeTimeMax;
};

