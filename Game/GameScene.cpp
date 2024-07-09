#include "GameScene.h"
#include "MyGame.h"
#include "Input/Input.h"
#include "Map.h"
#include "Game/PlayerCamera.h"
#include "Game/Player.h"
#include "Game/Ghost.h"
#include "Game/WalkEnemy.h"
#include "Game/RotateEnemy.h"
#include "Game/Ladder.h"
#include "Game/Crank.h"
#include "Game/Seed.h"

GameScene::GameScene(MyGame* myGame) {
	mMyGame = myGame;
}

void GameScene::Initialize() {
	mMap = std::make_shared<Map>(mMyGame);
	mMap->Initialize();
	//-----プレイヤー-----
	mPlayer = std::make_shared<Player>(mMyGame);
	mPlayer->Initialize();
	//-----敵-----
	mGhost = std::make_shared<Ghost>(mMyGame);
	mGhost->Initialize();
	mGhost->SetPlayer(mPlayer);
	mRotateEnemy = std::make_shared<RotateEnemy>(mMyGame);
	mRotateEnemy->Initialize();
	mRotateEnemy->SetPlayer(mPlayer);
	mWalkEnemies.resize(3);
	for (uint32_t i = 0; i < mWalkEnemies.size(); ++i) {
		mWalkEnemies[i] = std::make_shared<WalkEnemy>(mMyGame);
		mWalkEnemies[i]->Initialize();
	}
	mWalkEnemies[0]->SetTranslate({ -1.5f,0.0f,5.0f });
	mWalkEnemies[0]->SetMoveMin({ -3.5f,0.0f,3.0f });
	mWalkEnemies[0]->SetMoveMax({ -1.5f,0.0f,5.0f });
	mWalkEnemies[0]->SetDirection(WalkEnemy::DOWN);
	mWalkEnemies[1]->SetTranslate({ 4.5f,0.0f,-2.0f });
	mWalkEnemies[1]->SetMoveMin({ 1.5f,0.0f,-5.0f });
	mWalkEnemies[1]->SetMoveMax({ 4.5f,0.0f,-2.0f });
	mWalkEnemies[1]->SetDirection(WalkEnemy::DOWN);
	mWalkEnemies[2]->SetTranslate({ 5.5f,0.0f,-1.0f });
	mWalkEnemies[2]->SetMoveMin({ 0.5f,0.0f,-1.0f });
	mWalkEnemies[2]->SetMoveMax({ 5.5f,0.0f,1.0f });
	mWalkEnemies[2]->SetDirection(WalkEnemy::LEFT);
	//-----オブジェクト-----
	mCrank = std::make_shared<Crank>(mMyGame);
	mCrank->Initialize();
	mLadders.resize(3);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i] = std::make_shared<Ladder>(mMyGame);
		mLadders[i]->Initialize();
	}
	mLadders[0]->SetTranslate({ -0.5f,0.0f,-4.5f });
	mLadders[0]->SetHeight(3);
	mLadders[0]->SetDirection(Ladder::FRONT);
	mLadders[1]->SetTranslate({ 5.0f,0.0f,0.0f });
	mLadders[1]->SetHeight(3);
	mLadders[1]->SetRotate({ 0.0f,-kPi / 2.0f,0.0f });
	mLadders[1]->SetDirection(Ladder::RIGHT);
	mLadders[2]->SetTranslate({ 3.0f,0.0f,5.0f });
	mLadders[2]->SetHeight(1);
	mLadders[2]->SetDirection(Ladder::FRONT);
	mSeeds.resize(1);
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		mSeeds[i] = std::make_shared<Seed>(mMyGame);
		mSeeds[i]->Initialize();
	}
	mSeeds[0]->SetTranslate({ -0.5f,0.2f,4.0f });
}

void GameScene::Finalize() {

}

void GameScene::Update(std::shared_ptr<Input> input) {
	mMap->Update(input);
	//-----プレイヤー-----
	mPlayer->Update(input);
	//-----敵-----
	mGhost->Update(input);
	mRotateEnemy->Update(input);
	for (uint32_t i = 0; i < mWalkEnemies.size(); ++i) {
		mWalkEnemies[i]->Update(input);
	}
	//-----オブジェクト-----
	mCrank->Update(input);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i]->Update();
	}
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		mSeeds[i]->Update(input);
	}
	//-----当たり判定-----
	//衝突判定前の処理
	CollisionResult collisionResult;
	mPlayer->SetIsGround(false);

	//マップとプレイヤー
	for (uint32_t i = 0; i < mMap->GetBlocks().size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mMap->GetBlocks()[i]->mWorldAABB, collisionResult)) {
			if (collisionResult.normal.y >= cosf(kPi / 4.0f)) { //45°よりなだらかな場所に立てる
				mPlayer->SetIsGround(true);
			}
			//押し戻し
			Vector3 pos = mPlayer->GetTranslate();
			pos += collisionResult.normal * collisionResult.depth;
			mPlayer->SetTranslate(pos);
		}
	}

	//ゴーストとプレイヤー
	if (IsCollision(mPlayer->GetAABB(), mGhost->GetWorldAABB(), collisionResult)) {
		if (!mPlayer->GetIsEnemyHit()) {
			mPlayer->SetHp(mPlayer->GetHp() - 1);
		}
		mPlayer->SetIsEnemyHit(true);
	}

	//回転する敵とプレイヤー
	if (mRotateEnemy->GetIsAlive()) {
		if (IsCollision(mPlayer->GetAABB(), mRotateEnemy->GetWorldAABB(), collisionResult)) {
			if (!mPlayer->GetIsAttack()) {
				if (!mPlayer->GetIsEnemyHit()) {
					mPlayer->SetHp(mPlayer->GetHp() - 1);
				}
				mPlayer->SetIsEnemyHit(true);
			}
		}
		if (IsCollision(mPlayer->GetAABB(), mRotateEnemy->GetWorldAABB(), collisionResult)) {
			if (mPlayer->GetIsAttack()) {
				mRotateEnemy->SetIsAlive(false);
			}
		}
	}

	//回転する敵とマップ
	for (uint32_t i = 0; i < mMap->GetBlocks().size(); ++i) {
		if (IsCollision(mRotateEnemy->GetWorldAABB(), mMap->GetBlocks()[i]->mWorldAABB, collisionResult)) {
			Vector3 pos = mRotateEnemy->GetTranslate();
			pos.x += collisionResult.normal.x * collisionResult.depth;
			pos.z += collisionResult.normal.z * collisionResult.depth;
			mRotateEnemy->SetTranslate(pos);
		}
	}

	//歩いている敵とプレイヤー
	for (uint32_t i = 0; i < mWalkEnemies.size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mWalkEnemies[i]->GetWorldAABB(), collisionResult)) {
			if (!mPlayer->GetIsEnemyHit()) {
				mPlayer->SetHp(mPlayer->GetHp() - 1);
			}
			mPlayer->SetIsEnemyHit(true);
		}
		if (IsCollision(mPlayer->GetAABB(), mWalkEnemies[i]->GetWorldAABB(), collisionResult)) {
			if (mPlayer->GetIsAttack() == true) {
				mWalkEnemies[i]->SetIsAlive(false);
			}
		}
	}

	//はしごとプレイヤー
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mLadders[i]->GetWorldAABB(), collisionResult)) {
			mLadders[i]->SetIsHitPlayer(true);
		} else {
			mLadders[i]->SetIsHitPlayer(false);
		}
	}

	//クランクとプレイヤー
	if (IsCollision(mPlayer->GetAABB(), mCrank->GetWorldAABB(), collisionResult)) {
		mCrank->SetIsHit(true);
		mMyGame->GetCamera()->SetIsFixed(true);
	} else {
		mCrank->SetIsHit(false);
		mMyGame->GetCamera()->SetIsFixed(false);
	}

	//種とプレイヤー
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mSeeds[i]->GetWorldAABB(), collisionResult) && !mSeeds[i]->GetIsHit()) {
			if (!mSeeds[i]->GetIsHit()) {
				mPlayer->SetAttackCount(mPlayer->GetAttackCount() + 1);
			}
			mSeeds[i]->SetIsHit(true);
		}
	}

	bool isHitLadder = false;
	//プレイヤーとはしごが当たっているとき
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		if (mLadders[i]->GetIsHitPlayer() == true) {
			isHitLadder = true;
			//はしごの向き(ベクトル)
			Vector3 ladderVec = mLadders[i]->GetVec();
			//プレイヤーの向き
			Vector3 forwardVec = Multiply(Vector3(0.0f, 0.0f, 1.0f), MakeRotateYMatrix(mPlayer->GetRotate().y));
			//内積を計算
			float dotProduct = Dot(forwardVec, ladderVec);
			if (dotProduct >= cosf(kPi / 180.0f * 30.0f) || mPlayer->GetTranslate().y < mLadders[i]->GetHeight())
			{
				if (input->PushKey(DIK_W) || input->GetLStick().y >= 0.7f) {
					switch (mLadders[i]->GetDirection()) {
					case Ladder::FRONT:
						mPlayer->SetTranslate(
							{ mLadders[i]->GetTranslate().x,
							mPlayer->GetTranslate().y,
							mLadders[i]->GetTranslate().z - 1.5f }
						);
						if (mPlayer->GetTranslate().y >= mLadders[i]->GetHeight()) {
							mPlayer->SetTranslate({ mPlayer->GetTranslate().x,mPlayer->GetTranslate().y + 2.0f,mPlayer->GetTranslate().z + 2.0f });
						}
						break;
					case Ladder::BACK:
						mPlayer->SetTranslate(
							{ mLadders[i]->GetTranslate().x,
							mPlayer->GetTranslate().y,
							mLadders[i]->GetTranslate().z + 1.5f }
						);
						if (mPlayer->GetTranslate().y >= mLadders[i]->GetHeight()) {
							mPlayer->SetTranslate({ mPlayer->GetTranslate().x,mPlayer->GetTranslate().y + 2.0f,mPlayer->GetTranslate().z - 2.0f });
						}
						break;
					case Ladder::LEFT:
						mPlayer->SetTranslate(
							{ mLadders[i]->GetTranslate().x - 1.5f,
							mPlayer->GetTranslate().y,
							mLadders[i]->GetTranslate().z }
						);
						if (mPlayer->GetTranslate().y >= mLadders[i]->GetHeight()) {
							mPlayer->SetTranslate({ mPlayer->GetTranslate().x + 2.0f, mPlayer->GetTranslate().y + 2.0f,mPlayer->GetTranslate().z });
						}
						break;
					case Ladder::RIGHT:
						mPlayer->SetTranslate(
							{ mLadders[i]->GetTranslate().x + 1.5f,
							mPlayer->GetTranslate().y,
							mLadders[i]->GetTranslate().z }
						);
						if (mPlayer->GetTranslate().y >= mLadders[i]->GetHeight()) {
							mPlayer->SetTranslate({ mPlayer->GetTranslate().x - 2.0f, mPlayer->GetTranslate().y + 2.0f,mPlayer->GetTranslate().z });
						}
						break;
					}

					Vector3 pos = mPlayer->GetTranslate();
					pos.y += 0.2f;
					mPlayer->SetTranslate(pos);
				}
			}
		}
	}
	//はしごの1つにでも当たっているときに重力を0にする
	if (isHitLadder == true) {
		mPlayer->SetGravity(0.0f);
	} else {
		mPlayer->SetGravity(0.05f);
	}
	mPlayer->UpdateMatrix();
}

void GameScene::ModelDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mMap->DrawModel(commandList);
	//-----プレイヤー-----
	mPlayer->DrawModel(commandList);
	//-----敵-----
	mGhost->DrawModel(commandList);
	mRotateEnemy->DrawModel(commandList);
	for (uint32_t i = 0; i < mWalkEnemies.size(); ++i) {
		mWalkEnemies[i]->DrawModel(commandList);
	}
	//-----オブジェクト-----
	mCrank->DrawModel(commandList);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i]->DrawModel(commandList);
	}
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		mSeeds[i]->DrawModel(commandList);
	}
}

void GameScene::SpriteDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	//-----プレイヤー-----
	mPlayer->DrawSprite(commandList);
	//-----オブジェクト-----
	mCrank->DrawSprite(commandList);
}
