#include <ma_Model.h>
#include <ma_UtilityFunctions.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <AssimpConverter/AssimpConverter.h>
#include <iostream>

Mineanarchy::Model::Model(const std::string& file, std::vector<ma_Vertex>* vertices, std::vector<uint16_t>* indices) : fileName(file), vertices(vertices), indices(indices) {

}

void Mineanarchy::Model::createModel() {
    Assimp::Importer Importer;
    std::string gameDir;
    UtilityFunctions::getGameDirectory(gameDir);
	const aiScene* pScene = Importer.ReadFile((gameDir + "/" + fileName).c_str(),
		aiProcess_LimitBoneWeights |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
    if(pScene->mNumMeshes > 0) {
        aiMesh* mesh = pScene->mMeshes[0];
        vertices->resize(mesh->mNumVertices);
        for(size_t i = 0; i < mesh->mNumVertices; i++) {
            (*vertices)[i].pos.x = mesh->mVertices[i].x;
            (*vertices)[i].pos.y = mesh->mVertices[i].y;
            (*vertices)[i].pos.z = mesh->mVertices[i].z;
        }
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace Face = mesh->mFaces[i];
            //CORE_ASSERT(Face.mNumIndices == 3);
            indices->push_back(Face.mIndices[0]);
            indices->push_back(Face.mIndices[1]);
            indices->push_back(Face.mIndices[2]);
        }
    }
}

void Mineanarchy::Model::createModel(unsigned int i) {
    saModel = SA::SkeletalModel();
    Assimp::Importer Importer;
    std::string gameDir;
    UtilityFunctions::getGameDirectory(gameDir);
	const aiScene* pScene = Importer.ReadFile((gameDir + "/" + fileName).c_str(),
		aiProcess_LimitBoneWeights |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	AssimpConverter::Convert(pScene, saModel);
    saModel.Update(2);
    std::cout << saModel.GetNumMeshes() << std::endl;
    std::cout << "Model to be loaded: " << (gameDir + "/" + fileName).c_str() << std::endl;

    size_t numVerts = 0;
    for (unsigned int i = 0; i < saModel.GetNumMeshes(); ++i)
	{
		const SA::sAnimatedMesh& AnimMesh = saModel.GetMesh(i);

        numVerts += AnimMesh.NumVertices;
        vertices->resize(numVerts);
		for (unsigned int i = 0; i < AnimMesh.NumIndices; ++i)
		{
			unsigned int Index = AnimMesh.pIndices[i];
			glm::vec3 v = AnimMesh.pTransformedVertices[Index];
			
			indices->push_back(Index);
            (*vertices)[Index].pos = v;
		}
	}

    /*const SA::sAnimatedMesh& AnimMesh = saModel.GetMesh(i);

    vertices.resize(AnimMesh.NumVertices);
    for (unsigned int i = 0; i < AnimMesh.NumVertices; ++i)
    {
        vertices[i].pos = AnimMesh.pVertices[i];
    }

    indices.resize(AnimMesh.NumIndices);
    for(unsigned int i = 0; i < AnimMesh.NumIndices; i++)  {
        indices[i] = AnimMesh.pIndices[i];
    }*/
}

/*void Model::createModel(const std::vector<ma_Vertex>& vertices, const std::vector<uint16_t>& indices) {
    this->vertices = vertices;
    this->indices = indices;
}*/

void Mineanarchy::Model::update(float time) {
    saModel.Update(time);
    size_t numVerts = 0;
    for (unsigned int i = 0; i < saModel.GetNumMeshes(); ++i)
	{
		const SA::sAnimatedMesh& AnimMesh = saModel.GetMesh(i);

        numVerts += AnimMesh.NumVertices;
        vertices->resize(numVerts);
		for (unsigned int i = 0; i < AnimMesh.NumIndices; ++i)
		{
			unsigned int Index = AnimMesh.pIndices[i];
			glm::vec3 v = AnimMesh.pTransformedVertices[Index];
			
			(*indices)[i] = Index;
            (*vertices)[Index].pos = v;
		}
	}
}