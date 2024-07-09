#pragma once
#include "Transform.h"
#include "Math/MyMath.h"
#include <d3d12.h>
#include <memory>
#include <wrl.h>

class MyGame;
class Model;
class Texture;
class Camera;
class Input;
struct VertexData;

class GameObject {
public:
	GameObject(MyGame* myGame);
	virtual ~GameObject();
	virtual void Initialize() {}
	virtual void Update(std::shared_ptr<Input> input) {}
	virtual void DrawModel(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {}
	virtual void DrawSprite(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList) {}
	void UpdateMatrix();

	/// <summary>
	/// アクセッサ
	/// </summary>
	Transform GetTransform() const { return mTransform; }
	Vector3 GetScale() const { return mTransform.mScale; }
	Vector3 GetRotate() const { return mTransform.mRotate; }
	Vector3 GetTranslate() const { return mTransform.mTranslate; }
	void SetTransform(const Transform& transform) { mTransform = transform; }
	void SetScale(const Vector3& scale) { mTransform.mScale = scale; }
	void SetRotate(const Vector3& rotate) { mTransform.mRotate = rotate; }
	void SetTranslate(const Vector3& translate) { mTransform.mTranslate = translate; }

protected:
	MyGame* mMyGame;
	Transform mTransform;
};

