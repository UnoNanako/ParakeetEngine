#pragma once
#include "Framework.h"
#include "Transform.h"
#include <memory>

class Sprite;

class MyGame : public Framework {
private:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	//std::shared_ptr<GamePlayScene> mScene = nullptr;
	std::shared_ptr<Sprite> mSprite;
	Transform mSpriteTransform;
};

