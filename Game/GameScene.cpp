#include "GameScene.h"
#include "MyGame.h"
#include "Input/Input.h"
#include "Map.h"

GameScene::GameScene(MyGame* myGame){
	mMyGame = myGame;
}

void GameScene::Initialize(std::shared_ptr<DirectXCommon> dxCommon){
	mDxCommon = dxCommon;

	mMap = std::make_shared<Map>(mMyGame);
	mMap->Initialize();
}

void GameScene::Finalize(){

}

void GameScene::Update(std::shared_ptr<Input> input){
	mMap->Update(input);
}

void GameScene::ModelDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	mMap->DrawModel(commandList);
}

void GameScene::SpriteDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){

}
