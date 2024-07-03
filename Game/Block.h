#pragma once
#include "Transform.h"
#include "MapType.h"
#include <string>
#include <memory>

class Model;
struct AABB;

struct Block {
	AABB GetWorldAABB() {
		AABB ret;
		ret.mMax = mAABB.mMax + mTransform.mTranslate;
		ret.mMin = mAABB.mMin + mTransform.mTranslate;
		return ret;
	}

	std::string mName;
	MapType mType;
	Transform mTransform;
	AABB mAABB;
	std::shared_ptr<Model> mModel = nullptr;
};
