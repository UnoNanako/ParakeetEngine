#pragma once
#include "Transform.h"
#include "2D/Texture.h"
#include "Material.h"
#include "Math/Quaternion.h"
#include "VertexData.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <memory>
#include <map>

class DirectXCommon;
class Quaternion;

//ノード
struct Node {
	Matrix4x4 mLocalMatrix;
	std::string mName;
	std::vector<Node> mChildren;
};

//モデルデータ
struct ModelData {
	std::vector<VertexData> mVertices;
	std::vector<uint32_t> mIndices;
	MaterialData mMaterial;
	Node mRootNode;
};

//キーフレーム
template <typename tValue>
struct Keyframe {
	float mTime;
	tValue mValue;
};
using KeyframeVector3 = Keyframe<Vector3>;
using KeyframeQuaternion = Keyframe<Quaternion>;

template<typename tValue>
struct AnimationCurve {
	std::vector<Keyframe<tValue>> mKeyframe;
};

struct NodeAnimation {
	AnimationCurve<Vector3> mTranslate;
	AnimationCurve<Quaternion> mRotate;
	AnimationCurve<Vector3> mScale;
};

struct Animation {
	float mDuration; //アニメーション全体の尺（単位は秒）
	//NodeAnimationの集合。Node名でひけるようにしておく
	std::map<std::string, NodeAnimation> mNodeAnimations;
};

class Model{
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath);
	void Update();
	void Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, const Transform& transform);

	//Animationを解析する関数
	Animation LoadAnimation(const std::string& filePath);
	//ランバートかフォンかをセットする
	void SetShadeType(ShadeType shadeType) { mShadeType = shadeType; }
	
private:
	//glTFを読む関数
	void Load(const std::string& filePath);
	Node ReadNode(aiNode* node);
	//任意の時刻の値を取得する
	//Vector3 Ver
	Vector3 CalculateValue(const std::vector<KeyframeVector3>& keyframes, float time);
	//Quaternion Ver
	Quaternion CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time);
	//親のパスを取得
	std::string GetParentPath(const std::string& path);

private:
	ModelData mModelData;
	Matrix4x4 mLocalMatrix;
	std::unique_ptr<Texture> mTexture;
	Microsoft::WRL::ComPtr<ID3D12Resource> mVertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mIndexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mMaterialResource;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView{};
	Material* mMaterialData;
	//アニメーション
	Animation mAnimation;
	float mAnimationTime = 0.0f;
	bool mIsLoop = false; //アニメーションがループしているか
	ShadeType mShadeType = LAMBERT; //ランバートかフォンかを入れるメンバ
};

