#pragma once
#include <memory>

class WinApp;
class DirectXCommon;
class Input;
class ImGuiManager;
class SpriteCommon;
class ResourceManager;

class Framework{
public:
	//仮想フレームワーク
	virtual ~Framework() = default;
	//実行
	void Run();

	//std::shared_ptr<DirectXCommon> GetDxCommon() const { return mDxCommon; }
	//std::shared_ptr<ModelCommon> GetModelCommon() const { return mModelCommon; }
	//std::shared_ptr<ParticleCommon> GetParticleCommon() const { return mParticleCommon; }

protected:
	//初期化
	virtual void Initialize();
	//終了
	virtual void Finalize();
	//毎フレーム更新
	virtual void Update();
	//描画
	virtual void Draw() = 0;

protected:
	bool mEndRequest;

	std::shared_ptr<WinApp> mWinApp;
	std::shared_ptr<DirectXCommon> mDxCommon;
	std::shared_ptr<ImGuiManager> mImGui;
	std::shared_ptr<Input> mInput;
	std::shared_ptr<ResourceManager> mResourceManager;
	std::shared_ptr<SpriteCommon> mSpriteCommon;
	//std::shared_ptr<ModelCommon> mModelCommon;
	//std::shared_ptr<ParticleCommon> mParticleCommon;
};

