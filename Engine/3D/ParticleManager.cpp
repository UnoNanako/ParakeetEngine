#include "ParticleManager.h"
#include "Particle.h"
#include "Math/MyMath.h"
#include "Camera.h"
#include "2D/Texture.h"
#include "DirectXCommon.h"
#include "Transform.h"
#include "Material.h"
#include "Math/Random.h"
#include "3D/VertexData.h"
#include "imgui/imgui.h"

void ParticleManager::Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture) {
	mTexture = texture;

	mInstancingResourse = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(ParticleForGPU) * kMaxInstance);
	mInstancingResourse->Map(0, nullptr, reinterpret_cast<void**>(&mInstancingData));

	//SRVの作成
	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};
	instancingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instancingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instancingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instancingSrvDesc.Buffer.FirstElement = 0;
	instancingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instancingSrvDesc.Buffer.NumElements = kMaxInstance;
	instancingSrvDesc.Buffer.StructureByteStride = sizeof(ParticleForGPU);
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU = dxCommon->GetCPUDescriptorHandle();
	mInstancingSrvHandleGPU = dxCommon->GetGPUDescriptorHandle();
	dxCommon->GetDevice()->CreateShaderResourceView(mInstancingResourse.Get(), &instancingSrvDesc, instancingSrvHandleCPU);

	mVertexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(VertexData) * 6);
	mVertexResource->Map(0, nullptr, reinterpret_cast<void**>(&mVertexData));
	mVertexBufferView.BufferLocation = mVertexResource->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = sizeof(VertexData) * 6;
	mVertexBufferView.StrideInBytes = sizeof(VertexData); //1頂点のサイズ

	// 左上
	mVertexData[0].mPosition = { -0.5f, 0.5f, 0.0f, 1.0f };
	mVertexData[0].mTexcoord = { 0.0f, 0.0f };
	// 右上
	mVertexData[1].mPosition = { 0.5f, 0.5f, 0.0f, 1.0f };
	mVertexData[1].mTexcoord = { 1.0f, 0.0f };
	// 右下
	mVertexData[2].mPosition = { 0.5f, -0.5f, 0.0f, 1.0f };
	mVertexData[2].mTexcoord = { 1.0f, 1.0f };
	// 左上2
	mVertexData[3].mPosition = { -0.5f, 0.5f, 0.0f, 1.0f };
	mVertexData[3].mTexcoord = { 0.0f, 0.0f };
	// 右下2
	mVertexData[4].mPosition = { 0.5f, -0.5f, 0.0f, 1.0f };
	mVertexData[4].mTexcoord = { 1.0f, 1.0f };
	// 左下
	mVertexData[5].mPosition = { -0.5f, -0.5f, 0.0f, 1.0f };
	mVertexData[5].mTexcoord = { 0.0f, 1.0f };

	mMaterialResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(Material));
	mMaterialResource->Map(0, nullptr, reinterpret_cast<void**>(&mMaterialData));
	mMaterialData->mColor = { 1.0f,1.0f,1.0f,1.0f };

	mEmitter.mCount = 3; //発生数
	mEmitter.mFrequency = 0.5f; //0.5秒ごとに発生
	mEmitter.mFrequencyTime = 0.0f; //発生頻度用の時刻、0で初期化
	mEmitter.mTransform.mScale = { 1.0f,1.0f,1.0f };
	mEmitter.mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mEmitter.mTransform.mTranslate = { 0.0f,0.0f,0.0f };

	mIsPlaying = true;
}

void ParticleManager::Update(std::shared_ptr<Camera> camera) {
	const float kDeltaTime = 1.0f / 60.0f; //tを定義。とりあえず60fps
	if (mIsPlaying == true) {
		mEmitter.mFrequencyTime += kDeltaTime; //時刻を進める
	}
	if (mEmitter.mFrequency <= mEmitter.mFrequencyTime) { //頻度より大きいなら発生
		mParticles.splice(mParticles.end(), Emit(mEmitter)); //発生処理
		mEmitter.mFrequencyTime -= mEmitter.mFrequency; //余計に過ぎた時間も加味して頻度計算する
	}

	//Particle用のWorldViewProjectionMatrixをつくる
	mNumInstance = 0;
	for (std::list<Particle>::iterator iter = mParticles.begin(); iter != mParticles.end();) {
		(*iter).mCurrentTime += kDeltaTime; //経過時間を足す
		if ((*iter).mLifeTime <= (*iter).mCurrentTime) {
			iter = mParticles.erase(iter); //生存時間がすぎたparticleはlistから消す。戻り値が次のイテレータになる
			continue;
		}

		(*iter).mTransform.mTranslate += (*iter).mVelocity * kDeltaTime;

		if (mNumInstance < kMaxInstance) {
			//ビルボード
			Matrix4x4 backToFrontMatrix = MakeRotateYMatrix(0.0f);
			Matrix4x4 scaleMatrix = MakeScaleMatrix((*iter).mTransform.mScale);
			Matrix4x4 translateMatrix = MakeTranslateMatrix((*iter).mTransform.mTranslate);
			Matrix4x4 billboardMatrix = Multiply(backToFrontMatrix, Inverse(camera->GetViewMatrix()));
			billboardMatrix.m[3][0] = 0.0f; //平行移動成分はいらない
			billboardMatrix.m[3][1] = 0.0f;
			billboardMatrix.m[3][2] = 0.0f;
			Matrix4x4 worldMatrix = Multiply(scaleMatrix, Multiply(billboardMatrix, translateMatrix));
			//worldMatrix = MakeAffineMatrix((*particleIterator).mTransform.scale, (*particleIterator).mTransform.rotate, (*particleIterator).mTransform.translate);
			mInstancingData[mNumInstance].mWorld = worldMatrix;
			mInstancingData[mNumInstance].mColor = (*iter).mColor;
			//mAlpha = 1.0f - ((*particleIterator).currentTime / (*particleIterator).lifeTime);
			//instancingData[mNumInstance].color.w = mAlpha; //算出したaをGPUに送る
			++mNumInstance; //生きているParticleの数を1つカウントする
		}

		++iter; //次のイテレータに進める
	}
}

void ParticleManager::Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, mMaterialResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootDescriptorTable(1, mInstancingSrvHandleGPU);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	mTexture->Bind(commandList, 3);
	commandList->DrawInstanced(6, mNumInstance, 0, 0);
}

Particle ParticleManager::MakeParticle(const Vector3& translate) {
	Particle particle;
	particle.mCurrentTime = 0;
	particle.mLifeTime = Random::Rand(mInitLifeTimeMin, mInitLifeTimeMax);
	particle.mTransform.mScale = { 1.0f,1.0f,1.0f };
	particle.mTransform.mRotate = { 0.0f,0.0f,0.0f };
	particle.mVelocity = { Random::Rand(mInitVelocityMin.x,mInitVelocityMax.x), Random::Rand(mInitVelocityMin.y,mInitVelocityMax.y), Random::Rand(mInitVelocityMin.z,mInitVelocityMax.z) };
	particle.mColor = { Random::Rand(mInitColorMin.x,mInitColorMax.x),  Random::Rand(mInitColorMin.y,mInitColorMax.y), Random::Rand(mInitColorMin.z,mInitColorMax.z), 1.0f };
	Vector3 randomTranslate{ Random::Rand(mInitTranslateMin.x,mInitTranslateMax.x),Random::Rand(mInitTranslateMin.y,mInitTranslateMax.y),Random::Rand(mInitTranslateMin.z,mInitTranslateMax.z) };
	particle.mTransform.mTranslate = translate + randomTranslate;
	return particle;
}

std::list<Particle> ParticleManager::Emit(const Emitter& emitter) {
	std::list<Particle> particles;
	for (uint32_t count = 0; count < emitter.mCount; ++count) {
		particles.push_back(MakeParticle(emitter.mTransform.mTranslate));
	}
	return particles;
}
