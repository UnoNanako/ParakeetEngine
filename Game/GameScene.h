#pragma once
#include <memory>
#include <wrl.h>
#include <d3d12.h>
#include <vector>

class MyGame;
class DirectXCommon;
class Input;
class Map;
class Player;
class Ladder;

class GameScene{
public:
	GameScene(MyGame* myGame);
	void Initialize();
	void Finalize();
	void Update(std::shared_ptr<Input> input);
	void ModelDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void SpriteDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);

	std::shared_ptr<Player> GetPlayer() { return mPlayer; }

private:
	MyGame* mMyGame;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<Player> mPlayer;
	std::vector<std::shared_ptr<Ladder>> mLadders;

};

