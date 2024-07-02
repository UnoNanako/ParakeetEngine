#include "Model.h"
#include "DirectXCommon.h"
#include "2D/Texture.h"

void Model::Create(std::shared_ptr<DirectXCommon> dxCommon, const std::string& filePath) {
	Load(filePath);
	mLocalMatrix = mModelData.mRootNode.mLocalMatrix;
	//頂点
	mVertexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(VertexData) * mModelData.mVertices.size());
	mVertexBufferView.BufferLocation = mVertexResource->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = static_cast<UINT>(sizeof(VertexData) * mModelData.mVertices.size());
	mVertexBufferView.StrideInBytes = sizeof(VertexData);

	//頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	//書き込むためのアドレスを取得
	mVertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	std::memcpy(vertexData, mModelData.mVertices.data(), sizeof(VertexData) * mModelData.mVertices.size());// 頂点データをリソースにコピー

	//インデックス
	mIndexResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(uint32_t) * mModelData.mIndices.size());
	mIndexBufferView.BufferLocation = mIndexResource->GetGPUVirtualAddress();
	mIndexBufferView.SizeInBytes = static_cast<UINT>(sizeof(uint32_t) * mModelData.mIndices.size());
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	uint32_t* indexData = nullptr;
	mIndexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	std::memcpy(indexData, mModelData.mIndices.data(), sizeof(uint32_t) * mModelData.mIndices.size());// 頂点データをリソースにコピー

	//色
	//Sprite用のマテリアルリソースを作る
	mMaterialResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(Material));
	//書き込むためのアドレスを取得
	mMaterialResource->Map(0, nullptr, reinterpret_cast<void**>(&mMaterialData));
	mMaterialData->color = { 1.0f,1.0f,1.0f,1.0f };
	//SpriteはLightingしないのでfalseを設定する
	mMaterialData->enableLighting = true;
	mMaterialData->shininess = 100.0f;

	//Texture
	mTexture = std::make_unique<Texture>();
	mTexture->Create(dxCommon, mModelData.mMaterial.textureFilePath);
}

void Model::Update() {
}

void Model::Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, const Transform& transform) {
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, mMaterialResource->GetGPUVirtualAddress());
	transform.Bind(commandList, 1);
	mTexture->Bind(commandList, 3);
	commandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	commandList->IASetIndexBuffer(&mIndexBufferView);
	commandList->DrawIndexedInstanced(static_cast<UINT>(mModelData.mIndices.size()), 1, 0, 0, 0);
}

void Model::Load(const std::string& filePath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	mModelData.mRootNode = ReadNode(scene->mRootNode);
	assert(scene->HasMeshes()); //メッシュがないのは対応しない
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals()); //法線がないMeshは今回は非対応
		assert(mesh->HasTextureCoords(0)); //TexcoordがないMeshは今回は非対応
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
			VertexData vertex;
			vertex.mPosition = { position.x,position.y,position.z,1.0f };
			vertex.mNormal = { normal.x,normal.y,normal.z };
			vertex.mTexcoord = { texcoord.x,texcoord.y };
			//aiProcess_MakeLeftHandedはz*=-1で、右手->左手に変換するので手動で対処
			vertex.mPosition.x *= -1.0f;
			vertex.mNormal.x *= -1.0f;
			mModelData.mVertices.push_back(vertex);
		}

		//頂点インデックス
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices <= 4); //4頂点以下のみのサポート
			for (uint32_t i = 0; i < face.mNumIndices; ++i) {
				if (i == 3) {
					mModelData.mIndices.push_back(face.mIndices[i - 1]);
					mModelData.mIndices.push_back(face.mIndices[i]);
					mModelData.mIndices.push_back(face.mIndices[i - 3]);
				} else {
					mModelData.mIndices.push_back(face.mIndices[i]);
				}
			}
		}
		//materialを解析する
		mModelData.mMaterial.textureFilePath = "Resources/Default.png";
		for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
			aiMaterial* material = scene->mMaterials[materialIndex];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
				aiString textureFilePath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
				mModelData.mMaterial.textureFilePath = GetParentPath(filePath) + "/" + textureFilePath.C_Str();
			}
		}
	}
}

Node Model::ReadNode(aiNode* node) {
	Node ret;
	aiMatrix4x4 aiLocalMatrix = node->mTransformation; //nodeのlocalMatrixを取得
	aiLocalMatrix.Transpose(); //列ベクトル形式を行ベクトル形式に転置
	ret.mLocalMatrix.m[0][0] = aiLocalMatrix[0][0];
	ret.mLocalMatrix.m[0][1] = aiLocalMatrix[0][1];
	ret.mLocalMatrix.m[0][2] = aiLocalMatrix[0][2];
	ret.mLocalMatrix.m[0][3] = aiLocalMatrix[0][3];
	ret.mLocalMatrix.m[1][0] = aiLocalMatrix[1][0];
	ret.mLocalMatrix.m[1][1] = aiLocalMatrix[1][1];
	ret.mLocalMatrix.m[1][2] = aiLocalMatrix[1][2];
	ret.mLocalMatrix.m[1][3] = aiLocalMatrix[1][3];
	ret.mLocalMatrix.m[2][0] = aiLocalMatrix[2][0];
	ret.mLocalMatrix.m[2][1] = aiLocalMatrix[2][1];
	ret.mLocalMatrix.m[2][2] = aiLocalMatrix[2][2];
	ret.mLocalMatrix.m[2][3] = aiLocalMatrix[2][3];
	ret.mLocalMatrix.m[3][0] = aiLocalMatrix[3][0];
	ret.mLocalMatrix.m[3][1] = aiLocalMatrix[3][1];
	ret.mLocalMatrix.m[3][2] = aiLocalMatrix[3][2];
	ret.mLocalMatrix.m[3][3] = aiLocalMatrix[3][3];
	ret.mName = node->mName.C_Str(); //Node名を格納
	ret.mChildren.resize(node->mNumChildren); //子供の数だけ確保
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex) {
		//再帰的に読んで階層構造を作っていく
		ret.mChildren[childIndex] = ReadNode(node->mChildren[childIndex]);
	}
	return ret;
}

Animation Model::LoadAnimation(const std::string& filePath) {
	return Animation();
}

Vector3 Model::CalculateValue(const std::vector<KeyframeVector3>& keyframes, float time) {
	return Vector3();
}

Quaternion Model::CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time) {
	return Quaternion();

}

std::string Model::GetParentPath(const std::string& path){
	size_t pos = path.find_last_of("/\\");
	if (pos != std::string::npos) {
		return path.substr(0, pos);
	}
	return std::string();
}
