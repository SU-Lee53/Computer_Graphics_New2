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

	aiMesh* loaded = *scene->mMeshes;

	aiVector3D* loadedVertices = loaded->mVertices;
	int vertexCount = loaded->mNumVertices;
	vector<glm::vec3> vertices;
	vertices.reserve(vertexCount);
	copy(loadedVertices, loadedVertices + vertexCount, vertices);

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
	// 1. ����, �븻
	vector<glm::vec3> vertices;
	vertices.reserve(mesh->mNumVertices);

	aiVector3D* loadedVertices = mesh->mVertices;
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		// �븻�� ���Խ��Ѿ���
	}

	// 2. �ε���. ������ ��ŵ��. �ϴ� ���� ���� ���ٰ� ������
	vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces);

	aiFace* loadedFaces;
	if (mesh->HasFaces())
	{
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			loadedFaces = mesh->mFaces;
			int IndexCount = loadedFaces->mNumIndices;
			copy(loadedFaces->mIndices, loadedFaces->mIndices + IndexCount, indices.end());	// ������ �����ٰ� �ε����� �о�ִ´�
		}
	}

	// 3. ����. ������ ��ŵ. �굵 ���°��� ���ٰ� ������
	vector<RGB> colors;
	colors.reserve(vertices.size());

	aiColor4D* loadedColor;
	for (int i = 0; i < vertices.size(); i++)
	{
		loadedColor = *mesh->mColors;
		float container[] = {loadedColor->r, loadedColor->g, loadedColor->b};
		copy(container, container + 3, colors.end());
	}

	// VAO ������ ���� �ʿ��� ������ ���·� ����
	float* vertexContainer;
	unsigned int* indexContainer;
	float* colorContainer;

	copy(vertices.begin(), vertices.end(), vertexContainer);
	copy(indices.begin(), indices.end(), indexContainer);
	copy(colors.begin(), colors.end(), colorContainer);

	VAO* vao;

	// �ε����� ������ indexed�� ���� ����
	if (mesh->HasFaces())
	{
		vao = new VAO(vertexContainer, colorContainer, indexContainer, static_cast<int>(vertices.size()), static_cast<int>(indices.size()));
	}
	else
	{
		vao = new VAO(vertexContainer, colorContainer, static_cast<int>(vertices.size()));
	}

	vaoList.push_back(vao);
	
}


// �Ͼ�� �ؾ�����
// 1. STL ���� �� ������̱�
// 2. �׽�Ʈ