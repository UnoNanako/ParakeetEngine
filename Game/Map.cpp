#include "Map.h"
#include "ResourceManager.h"
#include "MyGame.h"
#include "ImGuiManager.h"
#include "3D/Model.h"
#include <fstream>
#include <Externals/nlohmann/json.hpp>

Map::Map(MyGame* myGame)
	: GameObject(myGame) {

}

void Map::Initialize() {
	mDxCommon = mMyGame->GetDxCommon();

	//jsonファイル読み込み
	//読み込むファイルの名前を作成
	std::ifstream ifs(kFilePath);
	if (ifs.good()) {
		nlohmann::json json;
		ifs >> json;

		auto manager = mMyGame->GetResourceManager();
		uint32_t blockCount = json["BlockCount"].get<uint32_t>();
		//読み込んだデータをそれぞれの変数に代入する
		for (uint32_t i = 0; i < blockCount; ++i) {
			nlohmann::json& blockData = json[std::format("Block{}", i)]; //これあとで理解

			std::shared_ptr<Block> block = std::make_unique<Block>();
			//モデルの番号を読み取る
			block->mName = blockData["Name"].get<std::string>();
			block->mType = blockData["MapType"].get<MapType>();
			block->mTransform.mScale.x = blockData["Scale"][0].get<float>();
			block->mTransform.mScale.y = blockData["Scale"][1].get<float>();
			block->mTransform.mScale.z = blockData["Scale"][2].get<float>();
			block->mTransform.mRotate.x = blockData["Rotate"][0].get<float>();
			block->mTransform.mRotate.y = blockData["Rotate"][1].get<float>();
			block->mTransform.mRotate.z = blockData["Rotate"][2].get<float>();
			block->mTransform.mTranslate.x = blockData["Translate"][0].get<float>();
			block->mTransform.mTranslate.y = blockData["Translate"][1].get<float>();
			block->mTransform.mTranslate.z = blockData["Translate"][2].get<float>();
			block->mAABB.mMax.x = blockData["Max"][0].get<float>();
			block->mAABB.mMax.y = blockData["Max"][1].get<float>();
			block->mAABB.mMax.z = blockData["Max"][2].get<float>();
			block->mAABB.mMin.x = blockData["Min"][0].get<float>();
			block->mAABB.mMin.y = blockData["Min"][1].get<float>();
			block->mAABB.mMin.z = blockData["Min"][2].get<float>();
			std::string path = kBlockModelPaths[block->mType];
			if (path.length() > 0) {
				block->mModel = manager->LoadModel(mDxCommon, kBlockModelPaths[block->mType]);
			}
			mBlocks.emplace_back(block);
		}
	}
	for (uint32_t i = 0; i < mBlocks.size(); ++i) {
		mBlocks[i]->mTransform.Create(mDxCommon);
		mBlocks[i]->mTransform.UpdateMatrix();
	}
}

void Map::Update() {
	ImGui::Begin("Map");
	if (ImGui::Button("Create")) {
		std::shared_ptr<Block> block = std::make_unique<Block>();
		block->mName = "NewBlock";
		block->mType = mMapTypeForImGui;
		std::string path = kBlockModelPaths[mMapTypeForImGui];
		if (path.length() > 0) {
			block->mModel = mMyGame->GetResourceManager()->LoadModel(mDxCommon, kBlockModelPaths[mMapTypeForImGui]);
		}
		block->mTransform.Create(mDxCommon);
		mBlocks.emplace_back(block);
	}

	ImGui::Separator();
	int i = 0;
	for (auto iter = mBlocks.begin(); iter != mBlocks.end();) {
		ImGui::InputText(std::format("Name##{}", i).c_str(), &(*iter)->mName);
		bool isErase = false;
		if (ImGui::TreeNode(std::format("{}##{}", (*iter)->mName, i).c_str())) {
			ImGui::DragFloat3(std::format("Scale##{}", i).c_str(), &(*iter)->mTransform.mScale.x, 0.01f);
			ImGui::DragFloat3(std::format("Rotate##{}", i).c_str(), &(*iter)->mTransform.mRotate.x, 0.01f);
			ImGui::DragFloat3(std::format("Translate##{}", i).c_str(), &(*iter)->mTransform.mTranslate.x, 0.01f);
			ImGui::DragFloat3(std::format("Max##{}", i).c_str(), &(*iter)->mAABB.mMax.x);
			ImGui::DragFloat3(std::format("Min##{}", i).c_str(), &(*iter)->mAABB.mMin.x);
			if (Combo(std::format("Type##{}", i).c_str(), (*iter)->mType)) {
				std::string path = kBlockModelPaths[(*iter)->mType];
				if (path.length() > 0) {
					(*iter)->mModel = mMyGame->GetResourceManager()->LoadModel(mDxCommon, kBlockModelPaths[(*iter)->mType]);
				}
			}
			if (ImGui::Button(std::format("Erase##{}", i).c_str())) {
				iter = mBlocks.erase(iter);
				isErase = true;
			}
			ImGui::TreePop();
		}
		if (!isErase) {
			++iter;
		}
		++i;
		ImGui::Separator();
	}

	if (ImGui::Button("Save")) {
		Save();
	}

	ImGui::End();

	for (uint32_t i = 0; i < mBlocks.size(); ++i) {
		mBlocks[i]->mTransform.UpdateMatrix();
	}
}

void Map::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	for (uint32_t i = 0; i < mBlocks.size(); ++i) {
		if (mBlocks[i]->mModel) {
			mBlocks[i]->mModel->Draw(commandList, mBlocks[i]->mTransform);
		}
	}
}

void Map::Save(){
	//mapJson書き込み
	std::ofstream file(kFilePath.c_str());
	nlohmann::json data;
	data["BlockCount"] = mBlocks.size();
	for (uint32_t i = 0; i < mBlocks.size(); ++i) {
		nlohmann::json& blockData = data[std::format("Block{}", i)]; //これあとで理解
		blockData["Name"] = mBlocks[i]->mName;
		blockData["MapType"] = mBlocks[i]->mType;
		blockData["Scale"].push_back(mBlocks[i]->mTransform.mScale.x);
		blockData["Scale"].push_back(mBlocks[i]->mTransform.mScale.y);
		blockData["Scale"].push_back(mBlocks[i]->mTransform.mScale.z);
		blockData["Rotate"].push_back(mBlocks[i]->mTransform.mRotate.x);
		blockData["Rotate"].push_back(mBlocks[i]->mTransform.mRotate.y);
		blockData["Rotate"].push_back(mBlocks[i]->mTransform.mRotate.z);
		blockData["Translate"].push_back(mBlocks[i]->mTransform.mTranslate.x);
		blockData["Translate"].push_back(mBlocks[i]->mTransform.mTranslate.y);
		blockData["Translate"].push_back(mBlocks[i]->mTransform.mTranslate.z);
		blockData["Max"].push_back(mBlocks[i]->mAABB.mMax.x);
		blockData["Max"].push_back(mBlocks[i]->mAABB.mMax.y);
		blockData["Max"].push_back(mBlocks[i]->mAABB.mMax.z);
		blockData["Min"].push_back(mBlocks[i]->mAABB.mMin.x);
		blockData["Min"].push_back(mBlocks[i]->mAABB.mMin.y);
		blockData["Min"].push_back(mBlocks[i]->mAABB.mMin.z);
	}
	file << data.dump(4) << std::endl;
}
