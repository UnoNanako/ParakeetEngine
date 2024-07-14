#pragma once
#include "Transform.h"
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
class RotateBridge;
class Gem;
class Star;
class Skydome;
class Sprite;

class GameScene{
public:
	GameScene(MyGame* myGame);
	void Initialize();
	void Finalize();
	void Update(std::shared_ptr<Input> input);
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
	void UpdateObject(std::shared_ptr<Input> input);
	void UpdateCollision(std::shared_ptr<Input> input);
	void GameInit();

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
	std::shared_ptr<RotateBridge> mRotateBridge;
	std::vector<std::shared_ptr<Gem>> mGems;
	std::shared_ptr<Star> mStar;
	std::shared_ptr<Skydome> mSkydome;

	//-----スプライト-----
	std::shared_ptr<Sprite> mTitle;
	std::shared_ptr<Sprite> mNowLoading;
	std::shared_ptr<Sprite> mGameClear;
	std::shared_ptr<Sprite> mGameOver;
	std::shared_ptr<Sprite> mAButton;
	Transform mTitleTransform;
	Transform mNowLoadingTransform;
	Transform mGameClearTransform;
	Transform mGameOverTransform;
	Transform mAButtonTransform;

	//-----シーン-----
	enum Scene {
		GAME,
		CLEAR,
		OVER
	};
	Scene mScene = GAME;
	bool mIsTransition = false;
	bool mIsTitleScene;

	//-----イージング-----
	Vector3 mInStart;
	Vector3 mInEnd;
	Vector3 mOutStart;
	Vector3 mOutEnd;
	float mInT;
	float mOutT;
};