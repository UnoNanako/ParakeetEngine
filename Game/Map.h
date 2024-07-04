#pragma once
#include "Transform.h"
#include "GameObject.h"
#include "Block.h"
#include <vector>
#include <string>

class Model;
class DirectXCommon;

class Map : public GameObject {
public:
	Map(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;

	std::vector<std::shared_ptr<Block>> GetBlocks() { return mBlocks; }

private:
	void Save();

private:
	const std::string kFilePath = "./Resources/Json/Map.json";
	std::shared_ptr<DirectXCommon> mDxCommon;
	std::vector<std::shared_ptr<Block>> mBlocks;
	MapType mMapTypeForImGui = MapType::NONE;
};

