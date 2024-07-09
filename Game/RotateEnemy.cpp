#include "RotateEnemy.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"
#include "Player.h"

RotateEnemy::RotateEnemy(MyGame* myGame)
	:GameObject(myGame) {
}

void RotateEnemy::Initialize() {
	mTransform.mScale = { 0.3f,0.3f,0.3f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 3.0f,0.0f,2.5f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/RotateEnemy/Giant.obj");
	mInitTranslate = { 3.0f,0.0f,2.5f }; //初期位置を保存
	mIsRotate = false;
	mIsAlive = true;
	mIsPlayerInView = false;
	mFovAngle = kPi / 2.0f;
	mLength = 3.0f;
	mState = ROTATE;
}

void RotateEnemy::Update(std::shared_ptr<Input> input) {
	switch (mState) {
	case ROTATE:
		Rotate();
		break;
	case CHASE:
		Chase();
		break;
	case RETURN:
		Return();
		break;
	}
	mLocalAABB.mMin = { -0.3f,-0.3f,-0.3f };
	mLocalAABB.mMax = { 0.3f,0.3f,0.3f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	mTransform.UpdateMatrix();
}

void RotateEnemy::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {
	if (mIsAlive) {
		mModel->Draw(commandList, mTransform);
	}
}

bool RotateEnemy::DetectPlayer() {
	//プレイヤーの位置を取得
	Vector3 position = mTransform.mTranslate;
	Vector3 playerPosition = mPlayer->GetTranslate();
	//敵からプレイヤーへのベクトルを計算する(正規化も)
	Vector3 toPlayer = playerPosition - position;
	toPlayer.Normalize();
	toPlayer.y = 0.0f;
	//敵の前方を表すベクトルを計算する
	//敵の向きはY軸回りに回転していると考え、Z軸が正面を向いていると仮定して回転行列を使って計算
	Vector3 forwardDirection = Multiply(Vector3(0.0f, 0.0f, 1.0f), MakeRotateYMatrix(mTransform.mRotate.y)); //仮にZ軸が正面を向いていると仮定
	//プレイヤーが敵の視野角内に収まっているかどうかを判定する
	//敵の前方ベクトルと敵からプレイヤーへの方向ベクトルの間の内積を計算し、その値が視野角の余弦以上かどうかで行う。
	float dotProduct = Dot(forwardDirection, toPlayer); //内積を計算
	float fovCosine = cosf(mFovAngle * 0.5f);
	//内積が視野角の余弦以上であれば、プレイヤーは視野角内に収まっている
	if (dotProduct >= fovCosine) {
		return true;
	} else {
		return false;
	}
}

void RotateEnemy::TrackPlayer() {
	//プレイヤーが視野角内にいるかどうか
	if (DetectPlayer()) {
		//プレイヤーの位置を取得
		Vector3 playerPosition = mPlayer->GetTranslate();
		//敵からプレイヤーへのベクトルを計算する
		Vector3 toPlayer = playerPosition - mTransform.mTranslate;
		//↑のベクトルの長さがmLengthよりも短い場合、プレイヤーが敵の攻撃範囲内にいると判断される。
		if (Length(toPlayer) <= mLength) {
			mState = CHASE;
			toPlayer.Normalize();
			//敵の向きをプレイヤーの方向に向ける
			//方向ベクトルを正規化し、敵の向きをプレイヤーの方向に向ける。
			//Y軸方向の回転角度を計算し、Y軸回りの回転を適用する。
			mTransform.mRotate.y = toPlayer.y;
			mTransform.mRotate.x = 0.0f;
			mTransform.mRotate.y = atan2(toPlayer.x, toPlayer.z);
			mTransform.mRotate.z = 0.0f;

			//敵をプレイヤーの方向に移動させる
			mMoveSpeed = 0.02f;
			Vector3 moveDirection = toPlayer * mMoveSpeed;
			mTransform.mTranslate.x += moveDirection.x;
			mTransform.mTranslate.z += moveDirection.z;
		} else {
			mState = RETURN;
		}
	} else {
		mState = RETURN;
	}
}

void RotateEnemy::Rotate() {
	//現在の時間を取得
	auto now = std::chrono::steady_clock::now();
	//5秒ごとに90°ずつ回転する
	if (std::chrono::duration_cast<std::chrono::seconds>(now - mLastRotationTime).count() >= 3) {
		mTransform.mRotate.y += (kPi / 2);
		mLastRotationTime = now;
	}
	if (DetectPlayer()) {
		//プレイヤーの位置を取得
		Vector3 playerPosition = mPlayer->GetTranslate();
		//敵からプレイヤーへのベクトルを計算する
		Vector3 toPlayer = playerPosition - mTransform.mTranslate;
		//↑のベクトルの長さがmLengthよりも短い場合、プレイヤーが敵の攻撃範囲内にいると判断される。
		if (Length(toPlayer) <= mLength) {
			mState = CHASE;
		}
	}
}

void RotateEnemy::Chase() {
	//プレイヤーが視野角内にいるかどうか
	if (DetectPlayer()) {
		//プレイヤーの位置を取得
		Vector3 playerPosition = mPlayer->GetTranslate();
		//敵からプレイヤーへのベクトルを計算する
		Vector3 toPlayer = playerPosition - mTransform.mTranslate;
		//↑のベクトルの長さがmLengthよりも短い場合、プレイヤーが敵の攻撃範囲内にいると判断される。
		if (Length(toPlayer) <= mLength) {
			toPlayer.Normalize();
			//敵の向きをプレイヤーの方向に向ける
			//方向ベクトルを正規化し、敵の向きをプレイヤーの方向に向ける。
			//Y軸方向の回転角度を計算し、Y軸回りの回転を適用する。
			mTransform.mRotate.y = toPlayer.y;
			mTransform.mRotate.x = 0.0f;
			mTransform.mRotate.y = atan2(toPlayer.x, toPlayer.z);
			mTransform.mRotate.z = 0.0f;

			//敵をプレイヤーの方向に移動させる
			mMoveSpeed = 0.02f;
			Vector3 moveDirection = toPlayer * mMoveSpeed;
			mTransform.mTranslate.x += moveDirection.x;
			mTransform.mTranslate.z += moveDirection.z;
		} else {
			mState = RETURN;
		}
	} else {
		mState = RETURN;
	}
}

void RotateEnemy::Return() {
	//プレイヤーが視野内にいなければ初期位置に戻る
	Vector3 vec = mInitTranslate - mTransform.mTranslate;
	if (Length(vec) <= 0.15f) {
		mTransform.mRotate = { 0.0f,0.0f,0.0f };
		mTransform.mRotate = { 0.0f,0.0f,0.0f };
		mState = ROTATE;
		return;
	}
	//初期位置の方へ向く
	mTransform.mRotate.x = 0.0f;
	mTransform.mRotate.y = atan2(vec.x, vec.z);
	mTransform.mRotate.z = 0.0f;
	vec.Normalize();
	//初期位置まで動く
	vec *= mMoveSpeed;
	mTransform.mTranslate += vec;
	if (DetectPlayer()) {
		//プレイヤーの位置を取得
		Vector3 playerPosition = mPlayer->GetTranslate();
		//敵からプレイヤーへのベクトルを計算する
		Vector3 toPlayer = playerPosition - mTransform.mTranslate;
		//↑のベクトルの長さがmLengthよりも短い場合、プレイヤーが敵の攻撃範囲内にいると判断される。
		if (Length(toPlayer) <= mLength) {
			mState = CHASE;
		}
	}
}
