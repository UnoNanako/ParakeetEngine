#pragma once
#include <string>
#include <map>
#include <memory>

class DirectXCommon;
class Texture;
class Model;

class ResourceManager{
public:
	std::shared_ptr<Texture> LoadTexture(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath);
	std::shared_ptr<Model> LoadModel(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath);
private:
	std::map<std::string, std::shared_ptr<Texture>> mTexture;
	std::map<std::string, std::shared_ptr<Model>> mModel;
};

