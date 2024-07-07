#pragma once
#include <string>
#include <map>
#include <memory>

class DirectXCommon;
class Texture;
class Model;

class ResourceManager{
public:
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	std::shared_ptr<Texture> LoadTexture(const std::string& filePath);
	std::shared_ptr<Model> LoadModel(const std::string& filePath);
private:
	std::shared_ptr<DirectXCommon> mDxCommon;
	std::map<std::string, std::shared_ptr<Texture>> mTexture;
	std::map<std::string, std::shared_ptr<Model>> mModel;
};

