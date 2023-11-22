#include "pch.h"
#include "Model.h"

Model::Model(const string& Filename)
{
	LoadModel(Filename);
}

Model::~Model()
{
	for (int i = 0; i < vaoList.size(); i++)
	{
		delete vaoList[i];
	}
}

bool Model::LoadModel(const string& Filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(Filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	if (!scene)
	{
		cout << "Failed to load model ( " << Filename << " ) " << importer.GetErrorString() << endl;
		return false;
	}

	LoadNode(scene->mRootNode, scene);
	LoadMaterials(scene);

}

void Model::ClearModel()
{
}

void Model::RenderModel()
{
	
}

void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[i], scene);
	}
	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}

}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	// 1. ����, �븻, �ؽ��� ��ǥ
	vector<float> vertices;
	vertices.reserve(mesh->mNumVertices);

	vector<float> normals;
	normals.reserve(mesh->mNumVertices);

	vector<float> textures;
	textures.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D vTemp = mesh->mVertices[i];
		aiVector3D nTemp = mesh->mNormals[i];
		vertices.insert(vertices.end(), { static_cast<float>(vTemp.x), static_cast<float>(vTemp.y), static_cast<float>(vTemp.z) });
		normals.insert(normals.end(), { static_cast<float>(nTemp.x), static_cast<float>(nTemp.y), static_cast<float>(nTemp.z) });

		if (mesh->mTextureCoords[0])
		{
			textures.insert(textures.end(), { static_cast<float>(mesh->mTextureCoords[0][i].x), static_cast<float>(mesh->mTextureCoords[0][i].y)});
		}
		else
		{
			textures.insert(textures.end(), { 0.0f, 0.0f });
		}

	}

	// 2. �ε���. ������ ��ŵ��. �ϴ� ���� ���� ���ٰ� ������
	vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces);

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace loadedFace = mesh->mFaces[i];
		for (int j = 0; j < loadedFace.mNumIndices; j++)
		{
			indices.push_back(loadedFace.mIndices[j]);
		}

	}

	// VAO ������ ���� �ʿ��� ������ ���·� ����

	float* vertexContainer = &vertices[0];
	float* normalContainer = &normals[0];
	float* texContainer = &textures[0];
	unsigned int* indexContainer = &indices[0];

	

	// VAO�� ���͸� �޾� �����ϴ� �����ڰ� �ʿ��ҵ���.....

	VAO* vao;

	// �ε����� ������ indexed�� ���� ����
	if (mesh->HasFaces())
	{
		vao = new VAO(vertexContainer, normalContainer, texContainer, indexContainer, static_cast<int>(vertices.size()), static_cast<int>(indices.size()), static_cast<int>(textures.size()));
	}
	else
	{
		vao = new VAO(vertexContainer, texContainer, static_cast<int>(vertices.size()));
	}

	vaoList.push_back(vao);
	
}

void Model::LoadMaterials(const aiScene* scene)
{

}


// �Ͼ�� �ؾ�����
// 1. STL ���� �� ������̱�
// 2. �׽�Ʈ