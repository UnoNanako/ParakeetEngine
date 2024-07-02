#include "Model.h"

void Model::Create(std::shared_ptr<DirectXCommon> dxCommon, std::shared_ptr<Texture> texture)
{
}

void Model::Update()
{
}

void Model::Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, const Transform& transform)
{
}

void Model::Load(const std::string& filePath){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	mModelData.rootNode = ReadNode(scene->mRootNode);
	assert(scene->HasMeshes()); //メッシュがないのは対応しない
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals()); //法線がないMeshは今回は非対応
		assert(mesh->HasTextureCoords(0)); //TexcoordがないMeshは今回は非対応
		//ここからMeshの中身(Face)の解析を行っていく
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3); //三角形のみのサポート
			//ここからFaceの中身(Vertex)の解析を行っていく
			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { position.x,position.y,position.z,1.0f };
				vertex.normal = { normal.x,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				//aiProcess_MakeLeftHandedはz*=-1で、右手->左手に変換するので手動で対処
				vertex.position.x *= -1.0f;
				vertex.normal.x *= -1.0f;
				mModelData.vertices.push_back(vertex);
				//materialを解析する
				mModelData.material.textureFilePath = "resources/default.png";
				for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
					aiMaterial* material = scene->mMaterials[materialIndex];
					if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
						aiString textureFilePath;
						material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
						mModelData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
					}
				}
			}
		}
	}
}

Node Model::ReadNode(aiNode* node)
{
	return Node();
}

Animation Model::LoadAnimationFile(const std::string& directoryPath, const std::string& filename)
{
	return Animation();
}

Vector3 Model::CalculateValue(const std::vector<KeyframeVector3>& keyfream, float time)
{
	return Vector3();
}
