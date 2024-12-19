#include <ma_Mesher.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <algorithm>
//#include <tbb/parallel_invoke.h>

Mineanarchy::Mesher::Mesher(std::vector<VoxelVertex>& vertices, std::vector<unsigned int>& indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid, const TerrainGenerator& terrainGenerator, IndexBufferManager& vboManager, IndexBufferManager& iboManager) : vertices(vertices), indices(indices), cubeSideLength(cubeSideLength), visibleChunkGrid(visibleChunkGrid), generator(terrainGenerator), vboManager(vboManager), iboManager(iboManager) {
    auto meshStart = std::chrono::high_resolution_clock::now();
    meshedChunks.reserve(2000000);
    //vertexMap.reserve(2000000);
    vertices.reserve(2000000);
    indices.reserve(2000000); // doesn't take long
    auto meshEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd - meshStart).count();
    std::cout << "pre alloc vertex and index buffer duration: " << totalDuration << std::endl;
}

void Mineanarchy::Mesher::MeshChunk(unsigned int x, unsigned int y, unsigned int z, std::vector<unsigned int>& chunkLocalIndices, std::vector<VoxelVertex>& chunkLocalVertices/*, std::unordered_map<vec3, unsigned int, Vec3Hasher>& vertexMap*/) {
    const unsigned char* voxels = visibleChunkGrid.getVoxelData();
    unsigned int chunkSize = visibleChunkGrid.getChunkSize();
    unsigned int gridHalfSideLength = visibleChunkGrid.getGridHalfSideLength();
    unsigned int gridX, gridY, gridZ;
    visibleChunkGrid.GetGridPosition(gridX, gridY, gridZ);

    unsigned int currentChunkX = gridX - gridHalfSideLength + x; // x,y, and z as in the grids current position
    unsigned int currentChunkY = gridY - gridHalfSideLength + y;
    unsigned int currentChunkZ = gridZ - gridHalfSideLength + z;
    std::unordered_map<vec3, unsigned int, Vec3Hasher> chunkLocalVertexMap;
    
    for(unsigned int cubeY = 0; cubeY < chunkSize; cubeY++) {
        for(unsigned int cubeZ = 0; cubeZ < chunkSize; cubeZ++) {
            for(unsigned int cubeX = 0; cubeX < chunkSize; cubeX++) {
                unsigned int baseX = currentChunkX*chunkSize + cubeX;
                unsigned int baseY = currentChunkY*chunkSize + cubeY;
                unsigned int baseZ = currentChunkZ*chunkSize + cubeZ;
                unsigned int voxelX = x*chunkSize + cubeX;
                unsigned int voxelY = y*chunkSize + cubeY;
                unsigned int voxelZ = z*chunkSize + cubeZ;
                if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY, voxelZ)]) {
                    //tbb::concurrent_hash_map<vec3, unsigned int, Vec3Hasher>::accessor accessor;
                    auto getIndex = [&](const vec3& vertex) -> int {
                        
                        /*if (chunkLocalVertexMap.find(accessor, vertex)) {
                            return accessor->second; // Safely access the value
                        }*/
                        if (chunkLocalVertexMap.find(vertex) != chunkLocalVertexMap.end()) {
                            return chunkLocalVertexMap[vertex]; // Safely access the value
                        }
                        // Handle case where vertex is not found (return an invalid index, or throw an error)
                        return -1; // Example error value
                    };

                    // Function to get index from chunkLocalVertexMap

                    int faceVisible = 0;

                    if(baseZ > 0) {
                        if(voxelZ > 0) {
                            if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY, voxelZ-1)] == 0) faceVisible = 1;
                        } else {
                            if(visibleChunkGrid.GetVoxel(baseX, baseY, baseZ-1) == 0) faceVisible = 1;
                            /*if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY, baseZ-1)) != changedVoxels.end()) {
                                if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY, baseZ-1)) == 0) {
                                    faceVisible = 1;
                                }
                            } else {
                                if(generator.GetBlockType(baseX, baseY, baseZ-1) == 0) { // if baseZ is 0 it's the edge of the world and we will never see the face anyway
                                    faceVisible = 1;
                                }
                            }*/
                        }
                    }
                    
                    if(faceVisible) {
                        if(getIndex(vec3(baseX, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ)); // adding vertices wil lresult in a random order in the vector since its happening concurrently this is the problem
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY + 1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY + 1, baseZ));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX + 1, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY + 1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY + 1, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX+1, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX+1, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX+1, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX+1, baseY+1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY+1, baseZ));
                            chunkLocalVertexMap[vec3(baseX+1, baseY+1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                            //chunkLocalVertexMap[vec3(baseX+1, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        
                        //if(getIndex(vec3(baseX + 1, baseY, baseZ)) == -1) {
                            //vertices.push_back(glm::vec3(baseX + 1, baseY, baseZ));
                            //chunkLocalVertexMap.insert(accessor, vec3(baseX + 1, baseY, baseZ)); accessor->second = static_cast<unsigned int>(vertices.size() - 1);
                        //}
                        // Front face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY + 1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                    }
                    faceVisible = 0;
                    
                    if(voxelY < gridHalfSideLength*2*chunkSize-1) {
                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY+1, voxelZ)] == 0) faceVisible = 1;
                    } else {
                        if(visibleChunkGrid.GetVoxel(baseX, baseY+1, baseZ) == 0) faceVisible = 1;
                    }
                    if(faceVisible) {
                        if(getIndex(vec3(baseX, baseY+1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY+1, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY+1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY + 1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY + 1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY + 1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY + 1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY+1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY+1, baseZ));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY+1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        // Top Face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY + 1, baseZ+1))); // baseY could be 31
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY+1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                    }
                    faceVisible = 0;
                    
                    if(baseY > 0) {
                        if(voxelY > 0) {
                            if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY-1, voxelZ)] == 0) faceVisible = 1;
                        } else {
                            if(visibleChunkGrid.GetVoxel(baseX, baseY-1, baseZ) == 0) faceVisible = 1;
                        }
                    }
                    if(faceVisible) {
                        if(getIndex(vec3(baseX, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX+1, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX+1, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        // Bottom face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                    }
                    faceVisible = 0;

                    if(voxelZ < gridHalfSideLength*2*chunkSize-1) {
                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY, voxelZ+1)] == 0) faceVisible = 1;
                    } else {
                        if(visibleChunkGrid.GetVoxel(baseX, baseY, baseZ+1) == 0) faceVisible = 1;
                    }

                    if(faceVisible) {
                        if(getIndex(vec3(baseX, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY + 1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX+1, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX+1, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY+1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY+1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY+1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        // Back face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                    }
                    faceVisible = 0;
                    
                    if(voxelX < gridHalfSideLength*2*chunkSize-1) {
                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX+1, voxelY, voxelZ)] == 0) faceVisible = 1;
                    } else {
                        if(visibleChunkGrid.GetVoxel(baseX+1, baseY, baseZ) == 0) faceVisible = 1;
                    }

                    if(faceVisible) {
                        if(getIndex(vec3(baseX+1, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX+1, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX+1, baseY+1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX+1, baseY+1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX+1, baseY+1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX + 1, baseY + 1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX + 1, baseY + 1, baseZ));
                            chunkLocalVertexMap[vec3(baseX + 1, baseY + 1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        // Right face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY+1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX+1, baseY+1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                    }
                    faceVisible = 0;

                    if(baseX > 0) {
                        if(voxelX > 0) {
                            if(voxels[ConvertToVoxelMapRelativeIndex(voxelX-1, voxelY, voxelZ)] == 0) faceVisible = 1;
                        } else {
                            if(visibleChunkGrid.GetVoxel(baseX-1, baseY, baseZ) == 0) faceVisible = 1;
                        }
                    }

                    if(faceVisible) {
                        if(getIndex(vec3(baseX, baseY, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY+1, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY+1, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY+1, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY, baseZ+1)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY, baseZ+1));
                            chunkLocalVertexMap[vec3(baseX, baseY, baseZ+1)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        if(getIndex(vec3(baseX, baseY+1, baseZ)) == -1) {
                            chunkLocalVertices.push_back(glm::vec3(baseX, baseY+1, baseZ));
                            chunkLocalVertexMap[vec3(baseX, baseY+1, baseZ)] = static_cast<unsigned int>(chunkLocalVertices.size() - 1);
                        }
                        // Left face
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                        chunkLocalIndices.push_back(getIndex(vec3(baseX, baseY+1, baseZ+1)));
                    }
                }
            }
        }
    }

}

void Mineanarchy::Mesher::ScheduleMeshTask() {
    auto chunkMeshingStart = std::chrono::high_resolution_clock::now();
    unsigned int gridX, gridY, gridZ;
    unsigned int gridHalfSideLength = visibleChunkGrid.getGridHalfSideLength();
    visibleChunkGrid.GetGridPosition(gridX, gridY, gridZ);

    chunksToRender.clear();
    unsigned int numThreads = std::thread::hardware_concurrency(); // Get number of available threads

    //std::vector<std::unordered_map<vec3, unsigned int, Vec3Hasher>> chunkLocalVertexMaps;
    //std::vector<std::vector<glm::vec3>> chunkLocalVertices;
    std::vector<std::vector<unsigned int>> chunkLocalIndices;
    std::vector<std::vector<VoxelVertex>> chunkLocalVertices;
    //std::vector<std::unordered_map<vec3, unsigned int, Vec3Hasher>> chunkLocalVertexMaps;
    //chunkLocalVertexMaps.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    //chunkLocalVertices.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    chunkLocalIndices.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    chunkLocalVertices.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    //chunkLocalVertexMaps.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    for(unsigned int yi = 0; yi < gridHalfSideLength*2; yi++) {
        for(unsigned int zi = 0; zi < gridHalfSideLength*2; zi++) {
            for(unsigned int xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = gridX - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = gridY - gridHalfSideLength + yi;
                unsigned int currentChunkZ = gridZ - gridHalfSideLength + zi;
                unsigned int index = yi*gridHalfSideLength*gridHalfSideLength*4 + zi*gridHalfSideLength*2 + xi;
                if(meshedChunks.find(vec3(currentChunkX, currentChunkY, currentChunkZ)) != meshedChunks.end()) {
                    //std::cout << "previously meshed " << currentChunkX << ", " << currentChunkY << ", " << currentChunkZ << std::endl;
                    continue;
                }
                if (threads.size() >= numThreads) {
                    for (auto it = threads.begin(); it != threads.end();) {
                        if (it->joinable()) {
                            // Check if the thread is joinable and join it
                            it->join(); // Wait for the thread to finish
                            it = threads.erase(it); // Remove it from the vector
                        } else {
                            threads.erase(it);
                            ++it; // Move to the next thread
                        }
                    }
                }
                threads.emplace_back([&, index, xi, yi, zi]() {
                    MeshChunk(xi, yi, zi, chunkLocalIndices[index], chunkLocalVertices[index]);
                });
            }
        }
    }
    // wait for threads to finish
    AwaitChunkMeshing();
    auto chunkMeshingEnd = std::chrono::high_resolution_clock::now();
    auto arrayMergingStart = std::chrono::high_resolution_clock::now();

    int upperRange = gridHalfSideLength*2;
    
    for(unsigned int yi = 0; yi < gridHalfSideLength*2; yi++) {
        for(unsigned int zi = 0; zi < gridHalfSideLength*2; zi++) {
            for(unsigned int xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = gridX - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = gridY - gridHalfSideLength + yi;
                unsigned int currentChunkZ = gridZ - gridHalfSideLength + zi;

                if(meshedChunks.find(vec3(currentChunkX, currentChunkY, currentChunkZ)) != meshedChunks.end()) {
                    chunksToRender.push_back(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)]);
                    continue;
                }
                unsigned int index = yi*gridHalfSideLength*gridHalfSideLength*4 + zi*gridHalfSideLength*2 + xi;
                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)] = ChunkInfo();
                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboStartIndex = indices.size();
                
                //vertices.insert(vertices.end(), chunkLocalVertices[index].begin(), chunkLocalVertices[index].end());
                //unsigned int constant = vertices.size();
                unsigned int offset = vertices.size();
                for(unsigned int i = 0; i < chunkLocalVertices[index].size(); i++) {
                    vertices.push_back(chunkLocalVertices[index][i]);
                    /*if(vertexMap.find(vec3(chunkLocalVertices[index][i].pos.x, chunkLocalVertices[index][i].pos.y, chunkLocalVertices[index][i].pos.z)) == vertexMap.end()) {
                        //accessor->first = vec3(chunkLocalVertices[index][i].pos.x, chunkLocalVertices[index][i].pos.y, chunkLocalVertices[index][i].pos.z); // Set the key
                        //accessor->second = vertices.size(); // Set the value (index in the vertex array)
                        vertexMap[vec3(chunkLocalVertices[index][i].pos.x, chunkLocalVertices[index][i].pos.y, chunkLocalVertices[index][i].pos.z)] = vertices.size(); // Insert the entry into the map
                        /*if (!accessor.is_null()) {
                            accessor->second = vertices.size();
                        } else {
                            // Handle the case where the accessor is invalid
                            std::cerr << "Accessor is invalid!" << std::endl;
                        }
                        //vertexMap[vec3(chunkLocalVertices[index][i].pos.x, chunkLocalVertices[index][i].pos.y, chunkLocalVertices[index][i].pos.z)] = vertices.size();
                        vertices.push_back(chunkLocalVertices[index][i]);
                    }*//* else {
                        accessor->second = vertices.size();
                        vertices.push_back(chunkLocalVertices[index][i]);
                    }*/
                    //std::cout << "chunklocalvertices index: " << index << " i: " << i << std::endl;
                }
                for(unsigned int i = 0; i < chunkLocalIndices[index].size(); i++) {
                    unsigned int vertexIndex = chunkLocalIndices[index][i];
                    indices.push_back(vertexIndex + offset);
                    /*VoxelVertex vertex = chunkLocalVertices[index][vertexIndex];
                    if(vertexMap.find(vec3(vertex.pos.x, vertex.pos.y, vertex.pos.z)) != vertexMap.end()) {
                        indices.push_back(vertexMap[vec3(vertex.pos.x, vertex.pos.y, vertex.pos.z)]);
                    }*/
                    //std::cout << "chunklocalindices index: " << index << " i: " << i << " value: " << chunkLocalIndices[index][i] << std::endl;
                }
                
                //std::transform(chunkLocalIndices[index].begin(), chunkLocalIndices[index].end(), indices.end(), [constant](int val) {return val + constant;});
                //indices.insert(indices.end(), chunkLocalIndices[index].begin(), chunkLocalIndices[index].end());

                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboEndIndex = indices.size();
                //meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].vboEndIndex = vertices.size();
                chunksToRender.push_back(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)]);
            }
        }
    }
    //unsigned int localVerticesIndex = vertices.size();
    
    iboManager.FinalizeMesh(indices.size());
    vboManager.FinalizeMesh(vertices.size());
    auto arrayMergingEnd = std::chrono::high_resolution_clock::now();

    std::cout << "number of indices: " << indices.size() << " number of vertices: " << vertices.size() << std::endl;
    auto chunkMeshingDuration = std::chrono::duration_cast<std::chrono::microseconds>(chunkMeshingEnd - chunkMeshingStart).count();
    auto arrayMergingDuration = std::chrono::duration_cast<std::chrono::microseconds>(arrayMergingEnd - arrayMergingStart).count();
    std::cout << "concurrent chunk meshing time: " << chunkMeshingDuration << ", array merging time: " << arrayMergingDuration << std::endl; 
    /*tbb::parallel_for(size_t(0), chunkLocalVertexMaps.size(), [&](size_t i) {
        for(const auto& [key, value] : chunkLocalVertexMaps[i]) {
            tbb::concurrent_hash_map<vec3, unsigned int, Vec3Hasher>::accessor accessor;
            vertexMap.insert(accessor, key);
            accessor->second = value + localVerticesIndex;
        }
        localVerticesIndex += chunkLocalVertices[i].size();
    });*/

}

/*void Mineanarchy::Mesher::MergeChunk(std::vector<glm::vec3>& chunkLocalVertices, std::vector<std::pair<vec3, size_t>>& chunkLocalVertexMap) {
    for (const auto& vertex : chunkLocalVertexMap) {
        std::lock_guard<std::mutex> guard(mapMutex); // Lock the mutex
        auto newVertex = vertex;
        newVertex.second += vertices.size(); // Modify second element
        vertexMap.emplace(newVertex);
    }
    //vertexMap.insert(chunkLocalVertexMaps[i].begin(), chunkLocalVertexMaps[i].end());
    std::lock_guard<std::mutex> guard(verticesMutex);
    vertices.insert(vertices.end(), chunkLocalVertices.begin(), chunkLocalVertices.end());
}*/

void Mineanarchy::Mesher::AwaitChunkMeshing() {
    // Wait for all threads to finish
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

/*unsigned int Mineanarchy::Mesher::getIndexCount() {
    return numberOfIndices;
}*/

/*void Mineanarchy::Mesher::GetVoxel(unsigned int chunkX, unsigned int chunkY, unsigned int chunkZ, unsigned int cubeX, unsigned int cubeY, unsigned int cubeZ) {
    if(cubeX < visibleChunkGrid.getChunkSize() && cubeX >= 0)
}*/

unsigned int Mineanarchy::Mesher::getVertexCount() {
    return numberOfVertices;
}

unsigned int Mineanarchy::Mesher::ConvertToVoxelMapRelativeIndex(unsigned int xi, unsigned int yi, unsigned int zi) {
    unsigned int chunkSize = visibleChunkGrid.getChunkSize();
    return visibleChunkGrid.GetVoxelMapIndex(xi/chunkSize, yi/chunkSize, zi/chunkSize) + (xi%chunkSize) + (yi%chunkSize)*chunkSize*chunkSize + (zi%chunkSize)*chunkSize;
}

const std::vector<Mineanarchy::Mesher::ChunkInfo>& Mineanarchy::Mesher::GetChunksToRender() const {
    return chunksToRender;
}