#include "ResourceManager.h"
#include "DirectXCommon.h"
#include "2D/Texture.h"

std::shared_ptr<Texture> ResourceManager::Load(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath){
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
