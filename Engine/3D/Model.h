#pragma once
#include "Transform.h"
#include "2D/Texture.h"
#include "Material.h"
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
struct VertexData;

//ノード
struct Node {
	Matrix4x4 mLocalMatrix;
	std::string name;
	std::vector<Node> children;
};

//モデルデータ
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	Node rootNode;
};

//キーフレーム
template <typename tValue>
struct Keyframe {
	float time;
	tValue value;
};
using KeyframeVector3 = Keyframe<Vector3>;
using KeyframeQuaternion = Keyframe<Quaternion>;

template<typename tValue>
struct AnimationCurve {
	std::vector<Keyframe<tValue>> keyframe;
};

struct NodeAnimation {
	AnimationCurve<Vector3> translate;
	AnimationCurve<Quaternion> rotate;
	AnimationCurve<Vector3> scale;
};

struct Animation {
	float duration; //アニメーション全体の尺（単位は秒）
	//NodeAnimationの集合。Node名でひけるようにしておく
	std::map<std::string, NodeAnimation> nodeAnimations;
};

class Model{
public:
	void Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture);
	void Update();
	void Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, const Transform& transform);

	//glTFを読む関数
	void Load(const std::string& derectoryPath, const std::string& filename);
	Node ReadNode(aiNode* node);
	//Animationを解析する関数
	Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename);
	//任意の時刻の値を取得する
	//Vector3 Ver
	Vector3 CalculateValue(const std::vector<KeyframeVector3>& keyfream, float time);
	//Quaternion Ver
	Quaternion CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time);
private:
	std::shared_ptr<Texture> mTexture;
	Microsoft::WRL::ComPtr<ID3D12Resource> mVertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mIndexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mMaterialResource;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView{};
	uint32_t* mIndexData;
	Vector4* mMaterialData;
};

