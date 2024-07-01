#pragma once
#include <string>
#include <map>
#include <memory>

class DirectXCommon;
class Texture;

class ResourceManager{
public:
	std::shared_ptr<Texture> Load(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath);
private:
	std::map<std::string, std::shared_ptr<Texture>> mTexture;
};

