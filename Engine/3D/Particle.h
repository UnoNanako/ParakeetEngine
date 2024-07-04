#pragma once
#include "Math/MyMath.h"

//Particle構造体
struct Particle {
	Transform mTransform;
	Vector3 mVelocity;
	Vector4 mColor;
	float mLifeTime;
	float mCurrentTime;
};

struct ParticleForGPU {
	Matrix4x4 mWorld;
	Vector4 mColor;
};

struct Emitter {
	Transform mTransform; //エミッタのTransform
	uint32_t mCount; //発生数
	float mFrequency; //発生頻度
	float mFrequencyTime; //頻度用時刻
};