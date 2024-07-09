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
class Ghost;
class WalkEnemy;
class RotateEnemy;
class Ladder;
class Crank;
class Seed;

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
	//-----プレイヤー-----
	std::shared_ptr<Player> mPlayer;
	//-----敵-----
	std::shared_ptr<Ghost> mGhost;
	std::shared_ptr<RotateEnemy> mRotateEnemy;
	std::vector<std::shared_ptr<WalkEnemy>> mWalkEnemies;
	//-----オブジェクト-----
	std::shared_ptr<Crank> mCrank;
	std::vector<std::shared_ptr<Ladder>> mLadders;
	std::vector<std::shared_ptr<Seed>> mSeeds;
};

