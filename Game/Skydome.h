#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class Skydome : public GameObject{
public:
	Skydome(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;

private:
	std::shared_ptr<Model> mModel;
};

