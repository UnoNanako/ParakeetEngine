#include "ResourceManager.h"
#include "DirectXCommon.h"
#include "2D/Texture.h"
#include "3D/Model.h"

void ResourceManager::Initialize(std::shared_ptr<DirectXCommon> dxCommon){
	mDxCommon = dxCommon;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& filePath) {
	auto iter = mTexture.find(filePath);
	if (iter != mTexture.end()) {
		return iter->second;
	} else {
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->Create(mDxCommon, filePath);
		mTexture.emplace(filePath, texture);
		return texture;
	}
}

std::shared_ptr<Model> ResourceManager::LoadModel(const std::string& filePath) {
	auto iter = mModel.find(filePath);
	if (iter != mModel.end()) {
		return iter->second;
	} else {
		std::shared_ptr<Model> model = std::make_shared<Model>();
		model->Create(mDxCommon, filePath);
		mModel.emplace(filePath, model);
		return model;
	}
}
