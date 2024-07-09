#include "Ghost.h"
#include "Input/Input.h"
#include "Transform.h"
#include "3D/Model.h"
#include "3D/VertexData.h"
#include "2D/Texture.h"
#include "2D/Sprite.h"
#include "MyGame.h"
#include "ResourceManager.h"
#include "Player.h"

Ghost::Ghost(MyGame* myGame)
	:GameObject(myGame){
}

void Ghost::Initialize(){
	mTransform.mScale = { 0.5f,0.5f,0.5f };
	mTransform.mRotate = { 0.0f,0.0f,0.0f };
	mTransform.mTranslate = { 0.0f,0.0f,0.0f };
	mTransform.Create(mMyGame->GetDxCommon());
	mModel = mMyGame->GetResourceManager()->LoadModel("Resources/Models/Ghost/Ghost.obj");
}

void Ghost::Update(std::shared_ptr<Input> input){
	DetectPlayer();
	TrackPlayer();
	mLocalAABB.mMin = { -0.5f,-0.5f,-0.5f };
	mLocalAABB.mMax = { 0.5f,0.5f,0.5f };
	mWorldAABB = CalcWorldAABB(mLocalAABB, mTransform.mTranslate);
	mTransform.UpdateMatrix();
}

void Ghost::DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList){
	mModel->Draw(commandList, mTransform);
}

bool Ghost::DetectPlayer(){
	//プレイヤーの位置を取得
	Vector3 position = mTransform.mTranslate;
	Vector3 playerPosition = mPlayer->GetTranslate();
	//敵からプレイヤーへのベクトルを計算する(正規化も)
	Vector3 toPlayer = playerPosition - position;
	toPlayer.y = 0.0f;
	toPlayer.Normalize();
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

void Ghost::TrackPlayer(){
	//プレイヤーの位置を取得
	Vector3 playerPosition = mPlayer->GetTranslate();
	//敵からプレイヤーへのベクトルを計算する
	Vector3 toPlayer = playerPosition - mTransform.mTranslate;
	toPlayer.y = 0.0f;
	toPlayer.Normalize();
	//ゴーストの前方を表すベクトルを計算
	Vector3 forwardDirection = Multiply(Vector3(0.0f, 0.0f, 1.0f), MakeRotateYMatrix(mTransform.mRotate.y));
	//プレイヤーの前方を表すベクトルを計算
	Vector3 playerForwardDirection = Multiply(Vector3(0.0f, 0.0f, 1.0f), MakeRotateYMatrix(mPlayer->GetTransform().mRotate.y));
	forwardDirection.Normalize();
	playerForwardDirection.Normalize();
	//プレイヤーとゴーストが向き合っているかどうかを判定するため、内積を計算
	float dotProduct = Dot(forwardDirection, playerForwardDirection);
	//プレイヤーとゴーストが向き合っている場合
	if (dotProduct <= 0.0f) {
		//ゴーストを停止させる
		mIsPlayerInView = false;
	} else {
		//プレイヤーとゴーストが向き合っていない場合、プレイヤーを追尾する
		mIsPlayerInView = true;
	}

	//敵の向きをプレイヤーの方向に向ける
	//方向ベクトルを正規化し、敵の向きをプレイヤーの方向に向ける。
	//Y軸方向の回転角度を計算し、Y軸回りの回転を適用する。
	mTransform.mRotate.x = 0.0f;
	mTransform.mRotate.y = atan2(toPlayer.x, toPlayer.z);
	mTransform.mRotate.z = 0.0f;

	//敵をプレイヤーの方向に移動させる
	float moveSpeed = 0.01f;
	Vector3 moveDirection = toPlayer * moveSpeed;
	if (mIsPlayerInView == true){
		mTransform.mTranslate += moveDirection;
	}
}
