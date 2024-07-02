#include "ResourceManager.h"
#include "DirectXCommon.h"
#include "2D/Texture.h"
#include "3D/Model.h"

std::shared_ptr<Texture> ResourceManager::LoadTexture(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath) {
	auto iter = mTexture.find(filePath);
	if (iter != mTexture.end()) {
		return iter->second;
	} else {
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->Create(dxCommon, filePath);
		mTexture.emplace(filePath, texture);
		return texture;
	}
}

std::shared_ptr<Model> ResourceManager::LoadModel(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath) {
	auto iter = mModel.find(filePath);
	if (iter != mModel.end()) {
		return iter->second;
	} else {
		std::shared_ptr<Model> model = std::make_shared<Model>();
		model->Create(dxCommon, filePath);
		mModel.emplace(filePath, model);
		return model;
	}
}
