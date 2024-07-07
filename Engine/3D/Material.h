#pragma once
#include "Math/MyMath.h"
#include <string>

enum ShadeType {
	LAMBERT, //ランバート
	PHONG //フォン
};

//マテリアル
struct Material {
	Vector4 mColor;
	int32_t mEnableLighting;
	float mShininess;
	ShadeType mShadeType;
};

//マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
};