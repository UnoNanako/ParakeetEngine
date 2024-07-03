#pragma once
#include <memory>
#include <wrl.h>
#include <d3d12.h>

class MyGame;
class DirectXCommon;
class Input;
class Map;

class GameScene{
public:
	GameScene(MyGame* myGame);
	void Initialize(std::shared_ptr<DirectXCommon> dxCommon);
	void Finalize();
	void Update(std::shared_ptr<Input> input);
	void ModelDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void SpriteDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

private:
	MyGame* mMyGame;
	std::shared_ptr<DirectXCommon> mDxCommon;
	std::shared_ptr<Map> mMap;
};

