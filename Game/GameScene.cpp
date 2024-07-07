#include "GameScene.h"
#include "MyGame.h"
#include "Input/Input.h"
#include "Map.h"
#include "Game/Player.h"
#include "Game/Ladder.h"

GameScene::GameScene(MyGame* myGame) {
	mMyGame = myGame;
}

void GameScene::Initialize() {
	mMap = std::make_shared<Map>(mMyGame);
	mMap->Initialize();
	mPlayer = std::make_shared<Player>(mMyGame);
	mPlayer->Initialize();
	mLadders.resize(1);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i] = std::make_shared<Ladder>(mMyGame);
		mLadders[i]->Initialize();
	}
	mLadders[0]->SetTranslate({ -0.5f,0.0f,-4.5f });
	mLadders[0]->SetHeight(3);
	mLadders[0]->SetDirection(Ladder::FRONT);
}

void GameScene::Finalize() {

}

void GameScene::Update(std::shared_ptr<Input> input) {
	mMap->Update(input);
	mPlayer->Update(input);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i]->Update();
	}

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
	//はしごとプレイヤー
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		if (IsCollision(mPlayer->GetAABB(), mLadders[i]->GetWorldAABB(), collisionResult)) {
			mLadders[i]->SetIsHitPlayer(true);
		} else {
			mLadders[i]->SetIsHitPlayer(false);
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
	mPlayer->DrawModel(commandList);
	for (uint32_t i = 0; i < mLadders.size(); ++i) {
		mLadders[i]->DrawModel(commandList);
	}
}

void GameScene::SpriteDraw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	mPlayer->DrawSprite(commandList);
}
