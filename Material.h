#pragma once
#include "Math/MyMath.h"
#include <string>

//マテリアル
struct Material {
	Vector4 color;
};

//マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
};