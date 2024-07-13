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
#include "Game/RotateBridge.h"
#include "Game/Gem.h"
#include "Game/Star.h"
#include "Game/Skydome.h"
#include "2D/Sprite.h"
#include "ResourceManager.h"
#include "Math/Easing.h"

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
	mWalkEnemies.resize(4);
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
	mWalkEnemies[3]->SetTranslate({ 5.5f,0.0f,24.5f });
	mWalkEnemies[3]->SetMoveMin({ 0.0f,0.0f,19.5f });
	mWalkEnemies[3]->SetMoveMax({ 5.5f,0.0f,25.0f });
	mWalkEnemies[3]->SetDirection(WalkEnemy::DOWN);
	//-----オブジェクト-----
	mCrank = std::make_shared<Crank>(mMyGame);
	mCrank->Initialize();
	mLadders.resize(8);
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
	mLadders[3]->SetTranslate({ 3.0f,0.0f,19.0f });
	mLadders[3]->SetHeight(1);
	mLadders[3]->SetDirection(Ladder::BACK);
	mLadders[4]->SetTranslate({ -0.75f,0.0f,28.0f });
	mLadders[4]->SetHeight(1);
	mLadders[4]->SetRotate({ 0.0f,-kPi / 2.0f,0.0f });
	mLadders[4]->SetDirection(Ladder::RIGHT);
	mLadders[5]->SetTranslate({ 4.75f,0.0f,22.25f });
	mLadders[5]->SetHeight(3);
	mLadders[5]->SetRotate({ 0.0f,-kPi / 2.0f,0.0f });
	mLadders[5]->SetDirection(Ladder::RIGHT);
	mLadders[6]->SetTranslate({ -3.25f,1.0f,24.25f });
	mLadders[6]->SetHeight(2);
	mLadders[6]->SetDirection(Ladder::BACK);
	mLadders[7]->SetTranslate({ -3.25f,3.0f,23.0f });
	mLadders[7]->SetHeight(2);
	mLadders[7]->SetDirection(Ladder::BACK);
	mSeeds.resize(1);
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		mSeeds[i] = std::make_shared<Seed>(mMyGame);
		mSeeds[i]->Initialize();
	}
	mSeeds[0]->SetTranslate({ -0.5f,0.5f,4.0f });
	mRotateBridge = std::make_shared<RotateBridge>(mMyGame);
	mRotateBridge->Initialize();
	mRotateBridge->SetCrank(mCrank);
	mGems.resize(3);
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i] = std::make_shared<Gem>(mMyGame);
		mGems[i]->Initialize();
		mGems[i]->SetSpriteTranslate({ (1088.0f + i * 64.0f),10.0f,0.0f });
	}
	mGems[0]->SetTranslate({ 5.5f,1.5f,-5.0f });
	mGems[1]->SetTranslate({ 3.5f,0.5f,22.0f });
	mGems[2]->SetTranslate({ -3.25f,3.5f,19.75f });
	mStar = std::make_shared<Star>(mMyGame);
	mStar ->Initialize();
	mSkydome = std::make_shared<Skydome>(mMyGame);
	mSkydome->Initialize();
	//-----スプライト-----
	mNowLoading = std::make_shared<Sprite>();
	mNowLoading->Create(mMyGame->GetDxCommon(), mMyGame->GetResourceManager()->LoadTexture("Resources/Sprites/NowLoading.png"));
	mNowLoadingTransform.mScale = { 1.0f,1.0f,1.0f };
	mNowLoadingTransform.mRotate = { 0.0f,0.0f,0.0f };
	mNowLoadingTransform.mTranslate = { -1280.0f,0.0f,0.0f };
	mNowLoadingTransform.Create(mMyGame->GetDxCommon());

	//イージング
	mInStart = { -1280.0f,0.0f,0.0f };
	mInEnd = { 0.0f,0.0f,0.0f };
	mOutStart = { 0.0f,0.0f,0.0f };
	mOutEnd = { 1280.0f,0.0f,0.0f };
	mInT = 0.0f;
	mOutT = 1.0f;

	mIsTitleScene = true;
}

void GameScene::Finalize() {

}

void GameScene::Update(std::shared_ptr<Input> input) {
	switch (mScene) {
	case GAME:
		mIsTransition = false;
		//NowLoadingイージング処理
		mOutT += 0.05f;
		if (mOutT >= 1.0f) {
			mOutT = 1.0f;
			if (input->GetButton(XINPUT_GAMEPAD_A) || input->PushKey(DIK_SPACE)) {
				mIsTitleScene = false;
				mPlayer->SetIsOperatable(true);
			}
		}
		mNowLoadingTransform.mTranslate = Leap(mOutStart, mOutEnd, Easing::EaseInOutCubic(mOutT));
		mNowLoadingTransform.UpdateMatrix();
		mMyGame->GetCamera()->SetIsTitleScene(mIsTitleScene);
		UpdateObject(input);
		UpdateCollision(input);
		if (mPlayer->GetHp() == 0) {
			mScene = OVER;
		}
		if (mStar->GetIsPlayerHit()) {
			mScene = CLEAR;
		}
		break;

	case CLEAR:
		if (input->GetButton(XINPUT_GAMEPAD_A) || input->PushKey(DIK_SPACE)) {
			mIsTransition = true;
		}
		//NowLoadingイージング処理
		if (mIsTransition) {
			mInT += 0.05f;
			if (mInT >= 1.0f) {
				mInT = 1.0f;
				mIsTitleScene = true;
				GameInit();
				mScene = GAME;
				mOutT = 0.0f;
				mNowLoadingTransform.mTranslate = Leap(mOutStart, mOutEnd, Easing::EaseInOutCubic(mOutT));
				mNowLoadingTransform.UpdateMatrix();
			} else {
				mNowLoadingTransform.mTranslate = Leap(mInStart, mOutEnd, Easing::EaseInOutCubic(mOutT));
				mNowLoadingTransform.UpdateMatrix();
			}
		}
		break;

	case OVER:
		if (input->GetButton(XINPUT_GAMEPAD_A) || input->PushKey(DIK_SPACE)) {
			mIsTransition = true;
		}
		if (mIsTransition) {
			mInT += 0.05f;
			if (mInT >= 1.0f) {
				mInT = 1.0f;
				mIsTitleScene = true;
				GameInit();
				mScene = GAME;
				mOutT = 0.0f;
				mNowLoadingTransform.mTranslate = Leap(mOutStart, mOutEnd, Easing::EaseInOutCubic(mOutT));
				mNowLoadingTransform.UpdateMatrix();
			} else {
				mNowLoadingTransform.mTranslate = Leap(mInStart, mInEnd, Easing::EaseInOutCubic(mInT));
				mNowLoadingTransform.UpdateMatrix();
			}
		}
		break;
	}
}

void GameScene::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
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
	mRotateBridge->DrawModel(commandList);
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i]->DrawModel(commandList);
	}
	mStar->DrawModel(commandList);
	mSkydome->DrawModel(commandList);
}

void GameScene::DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	//-----プレイヤー-----
	mPlayer->DrawSprite(commandList);
	//-----オブジェクト-----
	mCrank->DrawSprite(commandList);
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i]->DrawSprite(commandList);
	}
	mNowLoading->Draw(commandList,mNowLoadingTransform);
}

void GameScene::DrawParticle(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	mPlayer->DrawParticle(commandList);
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i]->DrawParticle(commandList);
	}
}

void GameScene::UpdateObject(std::shared_ptr<Input> input){
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
	mRotateBridge->Update(input);
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i]->Update(input);
	}
	mStar->Update(input);
	mSkydome->Update(input);
}

void GameScene::UpdateCollision(std::shared_ptr<Input> input){
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

	//回転する橋とプレイヤー
	if (IsCollision(mPlayer->GetAABB(), mRotateBridge->GetOBB(), collisionResult)) {
		mPlayer->SetIsGround(true);
		Vector3 pos = mPlayer->GetTranslate();
		pos += collisionResult.normal * collisionResult.depth / 2;
		mPlayer->SetTranslate(pos);
	}
	if (IsCollision(mPlayer->GetAABB(), mRotateBridge->GetSideLOBB(), collisionResult)) {
		mPlayer->SetIsGround(true);
		Vector3 pos = mPlayer->GetTranslate();
		pos += collisionResult.normal * collisionResult.depth / 2;
		mPlayer->SetTranslate(pos);
	}
	if (IsCollision(mPlayer->GetAABB(), mRotateBridge->GetSideROBB(), collisionResult)) {
		mPlayer->SetIsGround(true);
		Vector3 pos = mPlayer->GetTranslate();
		pos += collisionResult.normal * collisionResult.depth / 2;
		mPlayer->SetTranslate(pos);
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

	//ジェムとプレイヤー
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mGems[i]->GetWorldAABB(), collisionResult)) {
			mGems[i]->SetIsHit(true);
		}
	}

	//スターとプレイヤー
	if (IsCollision(mPlayer->GetAABB(), mStar->GetWorldAABB(), collisionResult)) {
		mStar->SetIsPlayerHit(true);
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

void GameScene::GameInit(){

	mIsTitleScene = true;
	mPlayer->Initialize();
	mGhost->Initialize();
	mRotateEnemy->Initialize();
	for (uint32_t i = 0; i < mWalkEnemies.size(); ++i) {
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
	mWalkEnemies[3]->SetTranslate({ 5.5f,0.0f,24.5f });
	mWalkEnemies[3]->SetMoveMin({ 0.5f,0.0f,20.5f });
	mWalkEnemies[3]->SetMoveMax({ 5.5f,0.0f,24.5f });
	mWalkEnemies[3]->SetDirection(WalkEnemy::DOWN);
	mCrank->Initialize(); 
	for (uint32_t i = 0; i < mSeeds.size(); ++i) {
		mSeeds[i]->Initialize();
	}
	mSeeds[0]->SetTranslate({ -0.5f,0.5f,4.0f });
	mRotateBridge->Initialize();
	for (uint32_t i = 0; i < mGems.size(); ++i) {
		mGems[i]->Initialize();
		mGems[i]->SetSpriteTranslate({ (1088.0f + i * 64.0f),10.0f,0.0f });
	}
	mGems[0]->SetTranslate({ 5.5f,1.5f,-5.0f });
	mGems[1]->SetTranslate({ 3.5f,0.5f,22.0f });
	mGems[2]->SetTranslate({ -3.25f,3.5f,19.75f });
	mStar->Initialize();
}
