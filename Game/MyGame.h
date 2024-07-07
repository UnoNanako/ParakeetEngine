#pragma once
#include "Framework.h"
#include "Transform.h"
#include "GameScene.h"
#include <memory>

class Sprite;
class Model;
class PlayerCamera;

class MyGame : public Framework {
private:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

public:
	std::shared_ptr<PlayerCamera> GetCamera() { return mCamera; }

private:
	/*std::shared_ptr<Sprite> mSprite;
	std::shared_ptr<Model> mModel;
	Transform mSpriteTransform;
	Transform mModelTransform;*/
	std::shared_ptr<PlayerCamera> mCamera;
	std::unique_ptr<GameScene> mGameScene;
};

