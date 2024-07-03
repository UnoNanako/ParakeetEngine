#pragma once
#include "Framework.h"
#include "Transform.h"
#include "GameScene.h"
#include <memory>

class Sprite;
class Model;
class Camera;

class MyGame : public Framework {
private:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	/*std::shared_ptr<Sprite> mSprite;
	std::shared_ptr<Model> mModel;
	Transform mSpriteTransform;
	Transform mModelTransform;*/
	std::unique_ptr<GameScene> mGameScene;
	std::shared_ptr<Camera> mCamera;
};

