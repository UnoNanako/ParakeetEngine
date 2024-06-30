#pragma once
#include <memory>

class WinApp;
class DirectXCommon;

class Framework{
public:
	//仮想フレームワーク
	virtual ~Framework() = default;
	//初期化
	virtual void Initialize();
	//終了
	virtual void Finalize();
	//毎フレーム更新
	virtual void Update();
	//描画
	virtual void Draw() = 0;
	//終了チェック
	virtual bool IsEndRequest() const { return mEndRequest; }
	//実行
	void Run();

	//std::shared_ptr<DirectXCommon> GetDxCommon() const { return mDxCommon; }
	//std::shared_ptr<ModelCommon> GetModelCommon() const { return mModelCommon; }
	//std::shared_ptr<ParticleCommon> GetParticleCommon() const { return mParticleCommon; }

private:
	bool mEndRequest;

protected:
	std::shared_ptr<WinApp> mWinApp;
	std::shared_ptr<DirectXCommon> mDxCommon;
	//std::shared_ptr<ImGuiManager> mImgui;
	//std::shared_ptr<Input> mInput;
	//std::shared_ptr<SpriteCommon> mSpriteCommon;
	//std::shared_ptr<ModelCommon> mModelCommon;
	//std::shared_ptr<ParticleCommon> mParticleCommon;
};

