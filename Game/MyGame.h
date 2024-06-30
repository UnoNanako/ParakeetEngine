#pragma once
#include "Framework.h"
#include <memory>

class MyGame : public Framework {
private:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	//std::shared_ptr<GamePlayScene> mScene = nullptr;
};

