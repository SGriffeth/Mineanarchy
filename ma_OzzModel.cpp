#include <fstream>
#include <vector>
#include <ma_UtilityFunctions.h>
#include <ma_OzzModel.h>
#include <iostream>
#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

/*// Utility function to load a file into a vector of bytes
std::vector<uint8_t> ma_OzzModel::LoadFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }
    std::ifstream::pos_type file_size = file.tellg();
    std::vector<uint8_t> file_contents(file_size);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(file_contents.data()), file_size);
    return file_contents;
}*/
void Mineanarchy::ma_OzzModel::LoadAnimation(const std::string& animation_file, const std::string& skeleton_file, const std::string& mesh_file, std::vector<ma_Vertex>& vertices, std::vector<unsigned int>& indices) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(mesh_file.c_str(),
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    std::cout << "meshfile: " << mesh_file << std::endl;
    if (!scene || !scene->HasMeshes()) {
        std::cout << "scene: " << !scene << std::endl;
        std::cout << "Has meshes: " << !scene->HasMeshes() << std::endl;
        
        std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
        return;
    }

    /*size_t numVertices = 0;
    std::map<unsigned int, unsigned int> currentBoneWeightMap;
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            //std::cout << "Face " << i << ": ";
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                std::cout << face.mIndices[j] << " ";
                indices.push_back(face.mIndices[j]);
            }
            //std::cout << std::endl;
        }

        numVertices += mesh->mNumVertices;
        vertices.resize(numVertices);
        // Process bones in the mesh
        for (unsigned int j = 0; j < mesh->mNumBones; ++j) {
            aiBone* bone = mesh->mBones[j];
            std::string boneName = bone->mName.C_Str();
            
            //std::cout << "Bone name: " << boneName << std::endl;
            //std::cout << "Number of weights: " << bone->mNumWeights << std::endl;

            // Extract bone weights and indices
            for (unsigned int k = 0; k < bone->mNumWeights; ++k) {
                aiVertexWeight& weight = bone->mWeights[k];
                unsigned int vertexId = weight.mVertexId;
                if(currentBoneWeightMap[vertexId] > NUM_OF_BONES_PER_VERTEX-1) {
                    std::cout << "bone weight at index " << currentBoneWeightMap[vertexId] << " doesnt fit in vertex" << std::endl; 
                    //continue;
                }
                if(currentBoneWeightMap.find(vertexId) != currentBoneWeightMap.end()) {
                    currentBoneWeightMap[vertexId] = currentBoneWeightMap[vertexId] + 1;
                } else {
                    currentBoneWeightMap[vertexId] = 0;
                } 
                float boneWeight = weight.mWeight;
                vertices[vertexId].boneIndices[currentBoneWeightMap[vertexId]] = j;
                vertices[vertexId].boneWeights[currentBoneWeightMap[vertexId]] = boneWeight;

                //std::cout << "Vertex ID: " << vertexId << ", Weight: " << boneWeight << std::endl;
            }
        }
    }*/
    size_t numVertices = 0;
    for(size_t k = 0; k < scene->mNumMeshes; k++) { 
        aiMesh* mesh = scene->mMeshes[k];   
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            //std::cout << "Face " << i << ": ";
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                //std::cout << face.mIndices[j] << " ";
                indices.push_back(face.mIndices[j]);
            }
            //std::cout << std::endl;
        }

        std::vector<std::vector<std::pair<unsigned int, float>>> boneData(mesh->mNumVertices);

        // Collect bone weights for each vertex
        for (unsigned int j = 0; j < mesh->mNumBones; ++j) {
            const aiBone* bone = mesh->mBones[j];
            for (unsigned int k = 0; k < bone->mNumWeights; ++k) {
                const aiVertexWeight& weight = bone->mWeights[k];
                unsigned int vertexId = weight.mVertexId;
                float boneWeight = weight.mWeight;
                
                boneData[vertexId].emplace_back(j, boneWeight);
            }
        }

        // Process each vertex
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            numVertices += mesh->mNumVertices;
            vertices.resize(numVertices);
            ma_Vertex& vertex = vertices[i];
            vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            auto& vertexBonePairs = boneData[i];
            if(vertexBonePairs.size() > NUM_OF_BONES_PER_VERTEX) std::cout << "too many bones in vertex : vertexBonePairs has " << vertexBonePairs.size() << " bones" << std::endl;
            for(size_t j = 0; j < std::min(NUM_OF_BONES_PER_VERTEX, vertexBonePairs.size()); j++) {
                vertex.boneIndices[j] = vertexBonePairs[j].first;
                vertex.boneWeights[j] = vertexBonePairs[j].second;
            }
            
            // Initialize bone indices and weights to zero
            /*std::fill(std::begin(vertex.boneIndices), std::end(vertex.boneIndices), 0);
            std::fill(std::begin(vertex.boneWeights), std::end(vertex.boneWeights), 0.0f);

            // Sort and pick the top N influences
            auto& vertexBoneData = boneData[i];
            std::sort(vertexBoneData.begin(), vertexBoneData.end(), [](const std::pair<unsigned int, float>& a, const std::pair<unsigned int, float>& b) {
                return b.second < a.second; // Sort descending by weight
            });

            // Assign weights to vertex, limiting to NUM_OF_BONES_PER_VERTEX influences
            float totalWeight = 0.0f;
            for (int j = 0; j < std::min(NUM_OF_BONES_PER_VERTEX, vertexBoneData.size()); ++j) {
                vertex.boneIndices[j] = vertexBoneData[j].first;
                vertex.boneWeights[j] = vertexBoneData[j].second;
                totalWeight += vertex.boneWeights[j];
            }

            // Normalize weights
            if (totalWeight > 0.0f) {
                for (int j = 0; j < NUM_OF_BONES_PER_VERTEX; ++j) {
                    vertex.boneWeights[j] /= totalWeight;
                }
            }*/
        }
    }

    // A file in ozz is a ozz::io::File, which implements ozz::io::Stream
    // interface and complies with std FILE specifications.
    // ozz::io::File follows RAII programming idiom, which ensures that
    // the file will always be closed (by ozz::io::FileStream destructor).
    ozz::io::File animationFile(animation_file.c_str(), "rb");
    ozz::io::File skeletonFile(skeleton_file.c_str(), "rb");

    // Checks file status, which can be closed if filename is invalid.
    if (!animationFile.opened()) {
        std::cerr << "Cannot open file " << animation_file << "." << std::endl;
        assert(0);
    }

    // Checks file status, which can be closed if filename is invalid.
    if (!skeletonFile.opened()) {
        std::cerr << "Cannot open file " << skeleton_file << "." << std::endl;
        assert(0);
    }
    ozz::io::IArchive archiveAnimation(&animationFile);

    if (!archiveAnimation.TestTag<ozz::animation::Animation>()) {
        std::cerr << "Archive doesn't contain the expected object type animation." <<
            std::endl;
        assert(0);
    }

    ozz::io::IArchive archiveSkeleton(&skeletonFile);
    
    if (!archiveSkeleton.TestTag<ozz::animation::Skeleton>()) {
        std::cerr << "Archive doesn't contain the expected object type skeleton." <<
            std::endl;
        assert(0);
    }

    archiveSkeleton >> skeleton;
     archiveAnimation >> animation;
    /*// Read and deserialize the skeleton data
    ozz::animation::offline::RawSkeleton raw_skeleton;
    archive >> raw_skeleton;

    // Build the animation
    ozz::animation::offline::AnimationBuilder animation_builder;
    animation = *animation_builder(raw_animation);
    if (!animation) {
        std::cerr << "Failed to build animation from raw data." << std::endl;
        return false;
    }

    // Build the skeleton
    ozz::animation::offline::SkeletonBuilder skeleton_builder;
    skeleton = *skeleton_builder(raw_skeleton);
    if (!skeleton) {
        std::cerr << "Failed to build skeleton from raw data." << std::endl;
        return false;
    }
*/

}

void Mineanarchy::ma_OzzModel::UpdateBoneTransforms(std::vector<glm::mat4>& matrices, float _dt) {
    std::vector<ozz::math::SoaTransform> data;
    context_.Resize(skeleton.num_joints());
    data.resize(skeleton.num_joints());
    // Updates base animation time for main animation.
    controller_.Update(animation, _dt);

    // Setup sampling job.
    ozz::animation::SamplingJob sampling_job;
    sampling_job.animation = &animation;
    sampling_job.context = &context_;
    sampling_job.ratio = controller_.time_ratio();
    sampling_job.output = ozz::make_span(data);

    if (!sampling_job.Run()) {
      throw std::runtime_error("Failed to run sampling job");
    }
    matrices = ConvertAllSoATransformsToMatrices(data);

    std::cout << "number of bone transforms: " << data.size() << std::endl;
}

std::vector<glm::mat4> Mineanarchy::ma_OzzModel::ConvertAllSoATransformsToMatrices(const std::vector<ozz::math::SoaTransform>& soa_transforms) {
    std::vector<glm::mat4> allMatrices;

    for (const auto& soa_transform : soa_transforms) {
        /*
        
        */
        /*size_t numTransforms = 4; // Example, adjust based on actual SoA size

        for (size_t i = 0; i < numTransforms; ++i) {
            // Extract quaternion components
            float xValue = soa_transform.rotation.x[0];
            float yValue = soa_transform.rotation.y[0];
            float zValue = soa_transform.rotation.z[0];
            float wValue = soa_transform.rotation.w[0];

            // Create glm::quat from the extracted components
            glm::quat rotation(xValue, yValue, zValue, wValue);

            // Extract single value for translation and scale
            glm::vec3 translation(
                soa_transform.translation.x, // x component
                soa_transform.translation.y, // y component
                soa_transform.translation.z  // z component (assuming the same value is used)
            );
            glm::vec3 scale(
                soa_transform.scale.x, // x component
                soa_transform.scale.y, // y component
                soa_transform.scale.z  // z component (assuming the same value is used)
            );

            // Create transformation matrix
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, translation);
            transform = transform * glm::mat4_cast(rotation); // Rotation needs to be applied in matrix form
            transform = glm::scale(transform, scale);

            allMatrices.push_back(transform);
        }*/
        glm::vec3 position(soa_transform.translation.x[0], soa_transform.translation.y[0], soa_transform.translation.z[0]);
        glm::quat rotation(soa_transform.rotation.x[0], soa_transform.rotation.y[0], soa_transform.rotation.z[0], soa_transform.rotation.w[0]);
        glm::vec3 scale(soa_transform.scale.x[0], soa_transform.scale.y[0], soa_transform.scale.z[0]);

        glm::mat4 mat = glm::translate(glm::mat4(1.0f), position);
        mat *= glm::mat4_cast(rotation);
        mat = glm::scale(mat, scale);

        allMatrices.push_back(mat);
    }

    return allMatrices;
}