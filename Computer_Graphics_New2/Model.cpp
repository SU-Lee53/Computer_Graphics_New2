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
	// 1. 정점
	vector<glm::vec3> vertices;
	vertices.reserve(mesh->mNumVertices);

	aiVector3D* loadedVertices = mesh->mVertices;
	copy(loadedVertices, loadedVertices + mesh->mNumVertices, vertices.begin());

	// 2. 인덱스. 없으면 스킵함. 일단 없는 경우는 없다고 생각함
	vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces);

	aiFace* loadedFaces;
	if (mesh->HasFaces())
	{
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			loadedFaces = mesh->mFaces;
			int IndexCount = loadedFaces->mNumIndices;
			copy(loadedFaces->mIndices, loadedFaces->mIndices + IndexCount, indices.end());	// 벡터의 끝에다가 인덱스를 밀어넣는다
		}
	}

	// 3. 색상. 없으면 스킵. 얘도 없는경우는 없다고 생각함
	vector<RGB> colors;
	colors.reserve(vertices.size());

	aiColor4D* loadedColor;
	for (int i = 0; i < vertices.size(); i++)
	{
		loadedColor = *mesh->mColors;
		float container[] = {loadedColor->r, loadedColor->g, loadedColor->b};
		copy(container, container + 3, colors.end());
	}

	// VAO 생성을 위해 필요한 데이터 형태로 복사
	float* vertexContainer;
	unsigned int* indexContainer;
	float* colorContainer;

	copy(vertices.begin(), vertices.end(), vertexContainer);
	copy(indices.begin(), indices.end(), indexContainer);
	copy(colors.begin(), colors.end(), colorContainer);

	VAO* vao;

	// 인덱스가 있으면 indexed로 버퍼 생성
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


