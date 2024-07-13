#pragma once
#include "GameObject.h"
#include "Transform.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

struct OBB;
class Crank;

class RotateBridge : public GameObject{
public:
	RotateBridge(MyGame* myGame);
	void Initialize()override;
	void Update(std::shared_ptr<Input> input)override;
	void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList)override;
	OBB CalculateOBB(const Vector3& translate, const Vector3& size);

	/// <summary>
	/// アクセッサ
	/// </summary>
	OBB GetOBB() { return mOBB; }
	OBB GetSideLOBB() { return mSideLOBB; }
	OBB GetSideROBB() { return mSideROBB; }
	Vector3 GetWorldPosition() { return Vector3{ mTransform.mMatWorld.m[3][0],mTransform.mMatWorld.m[3][1],mTransform.mMatWorld.m[3][2] }; }
	void SetRotate(Vector3 rotate) { mTransform.mRotate = rotate; }
	void SetCrank(std::shared_ptr<Crank> crank) { mCrank = crank; }

private:
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Crank> mCrank;
	OBB mOBB;
	OBB mSideLOBB;
	OBB mSideROBB;
};

