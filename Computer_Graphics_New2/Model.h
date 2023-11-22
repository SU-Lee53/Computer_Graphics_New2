#pragma once
#include <assimp/BaseImporter.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class Model
{
public:
	Model(const string& Filename);
	~Model();

	bool LoadModel(const string& Filename);
	void ClearModel();
	void RenderModel();

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	vector<VAO*> GetVAO() { return vaoList; }


private:
	vector<VAO*> vaoList;


};

