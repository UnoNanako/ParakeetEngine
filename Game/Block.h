#pragma once
#include "Transform.h"
#include "MapType.h"
#include <string>
#include <memory>

class Model;
struct AABB;

struct Block {
	std::string mName;
	MapType mType;
	Transform mTransform;
	AABB mLocalAABB;
	AABB mWorldAABB;
	std::shared_ptr<Model> mModel = nullptr;
};
