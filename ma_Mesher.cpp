#include <ma_Mesher.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
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

/*void Mineanarchy::Mesher::InsertVertices(const std::vector<std::pair<Mineanarchy::Mesher::vec3, size_t>>& verticesToInsert) {
    for (const auto& [vertex, index] : verticesToInsert) {
        //std::lock_guard<std::mutex> lock(mapMutex); // Lock for safe access
        vertexMap.emplace(vertex, index); // Insert into the map
    }
}*/

void Mineanarchy::Mesher::ProcessChunk(unsigned int currentChunkX, unsigned int currentChunkY, unsigned int currentChunkZ, std::vector<glm::vec3>& vertices) {
    unsigned int chunkSize = visibleChunkGrid.getChunkSize();
    meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)] = ChunkInfo(vertices.size());
    meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].meshedPreviously = 0;
    for (unsigned int cubeY = 0; cubeY < chunkSize + 1; cubeY++) {
        for (unsigned int cubeZ = 0; cubeZ < chunkSize + 1; cubeZ++) {
            for (unsigned int cubeX = 0; cubeX < chunkSize + 1; cubeX++) {
                const vec3 vertex = vec3(currentChunkX * chunkSize + cubeX,
                                   currentChunkY * chunkSize + cubeY,
                                   currentChunkZ * chunkSize + cubeZ);
                tbb::concurrent_hash_map<vec3, unsigned int, Vec3Hasher>::const_accessor accessor;
                if(!vertexMap.find(accessor, vertex)) {
                    vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
                    //tempVertices.emplace_back(vertex, vertices.size() - 1); // consider using unordered map instead of vector of pairs
                }
                
            }
        }
    }
    meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].vboEndIndex = vertices.size();

    // Insert into the map
    //InsertVertices(tempVertices);
}

void Mineanarchy::Mesher::Mesh() { // beware culling produces weird unexplainable effects in wireframe mode
    const unsigned char* voxels = visibleChunkGrid.getVoxelData();
    const std::unordered_map<VisibleChunkGrid::vec3, unsigned int, VisibleChunkGrid::Vec3Hasher>& changedVoxels = visibleChunkGrid.GetChangedVoxels();
    unsigned int chunkSize = visibleChunkGrid.getChunkSize();
    unsigned int gridHalfSideLength = visibleChunkGrid.getGridHalfSideLength();
    unsigned int startingX, startingY, startingZ;
    unsigned int previousX, previousY, previousZ;
    visibleChunkGrid.GetPrevGridPosition(previousX, previousY, previousZ);
    visibleChunkGrid.GetGridPosition(startingX, startingY, startingZ);
    unsigned int gridX = startingX;
    unsigned int gridY = startingY;
    unsigned int gridZ = startingZ;
    std::cout << "gridX: " << gridX << std::endl;
    std::cout << "gridY: " << gridY << std::endl;
    std::cout << "gridZ: " << gridZ << std::endl;
    startingX -= gridHalfSideLength;
    startingY -= gridHalfSideLength;
    startingZ -= gridHalfSideLength;
    startingX *= chunkSize;
    startingY *= chunkSize;
    startingZ *= chunkSize;

    unsigned int numThreads = std::thread::hardware_concurrency(); // Get number of available threads

    chunksToRender.clear();
    auto verticesStart = std::chrono::high_resolution_clock::now();
    //std::chrono::microseconds mapDuration(0);
    std::vector<std::vector<glm::vec3>> chunkLocalVertices;
    std::vector<std::unordered_map<vec3, size_t, Vec3Hasher>> chunkLocalVertexMaps;
    chunkLocalVertices.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    chunkLocalVertexMaps.resize(gridHalfSideLength*2*gridHalfSideLength*2*gridHalfSideLength*2);
    /*for (auto& vec : chunkLocalVertices) {
        vec.resize(4); // Resize each inner vector as needed
    }*/

    // Step 1: Create a temporary vector to hold the vertices and their indices
    //std::vector<std::pair<vec3, unsigned int>> tempVertices;
    // Add vertices for chunks that haven't been meshed previously
    for(unsigned int yi = 0; yi < gridHalfSideLength*2; yi++) {
        for(unsigned int zi = 0; zi < gridHalfSideLength*2; zi++) {
            for(unsigned int xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = gridX - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = gridY - gridHalfSideLength + yi;
                unsigned int currentChunkZ = gridZ - gridHalfSideLength + zi;
                if(meshedChunks.find(vec3(currentChunkX, currentChunkY, currentChunkZ)) != meshedChunks.end()) {
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
                unsigned int vertexIndex = yi * gridHalfSideLength * 2 * gridHalfSideLength * 2 + zi * gridHalfSideLength * 2 + xi;
                //ProcessChunk(currentChunkX, currentChunkY, currentChunkZ, chunkLocalVertices[vertexIndex], chunkLocalVertexMaps[vertexIndex]);
                threads.emplace_back([&, vertexIndex, currentChunkX, currentChunkY, currentChunkZ]() {
                    ProcessChunk(currentChunkX, currentChunkY, currentChunkZ, chunkLocalVertices[vertexIndex]);
                });
                /*// If we have reached the maximum number of threads, wait for any to finish
                if (threads.size() >= numThreads) {
                    for (auto it = threads.begin(); it != threads.end(); ) {
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
                threads.emplace_back([this, currentChunkX, currentChunkY, currentChunkZ]() {
                    ProcessChunk(currentChunkX, currentChunkY, currentChunkZ);
                });*/
            }
        }
    }
    AwaitChunkMeshing();
    auto verticesEnd = std::chrono::high_resolution_clock::now();

    /*// After joining threads, merge:
    for (unsigned int i = 0; i < chunkLocalVertices.size(); i++) {
        for(unsigned int j = 0; j < chunkLocalVertexMaps[i].size(); j++) {
            chunkLocalVertexMaps[i][j].second = chunkLocalVertexMaps[i][j].second + vertices.size();
            vertexMap.emplace(chunkLocalVertexMaps[i][j]);
        }
        for(unsigned int j = 0; j < chunkLocalVertices[i].size(); j++) {
            vertices.push_back(chunkLocalVertices[i][j]);
        }
        //vertices.insert(vertices.end(), local.begin(), local.end());
    }*/
    //std::vector<std::pair<vec3, unsigned int>> tempVertexMap; // Adjust types as necessary
    //std::vector<glm::vec3> tempVertices; // Replace VertexType with your vertex type
/*
for (unsigned int i = 0; i < chunkLocalVertexMaps.size(); i++) {
        for (const auto& vertex : chunkLocalVertexMaps[i]) {
            auto newVertex = vertex;
            newVertex.second += vertices.size(); // Modify second element
            vertexMap.emplace(newVertex);
        }
        vertices.insert(vertices.end(), chunkLocalVertices[i].begin(), chunkLocalVertices[i].end());
    }*/
    auto emplacingStart = std::chrono::high_resolution_clock::now();
    unsigned int currentIndex = 0;
    unsigned int verticesCount = vertices.size();
    std::vector<std::thread> mapThreads;
    for (unsigned int i = 0; i < chunkLocalVertices.size(); i++) {
        mapThreads.push_back(std::thread([&, i, currentIndex, verticesCount]() {
            for(unsigned int j = 0; j < chunkLocalVertices[i].size(); j++) {
                chunkLocalVertexMaps[i].emplace(vec3(chunkLocalVertices[i][j].x, chunkLocalVertices[i][j].y, chunkLocalVertices[i][j].z), j + currentIndex + verticesCount);
            }
        }));
        
        currentIndex += chunkLocalVertices[i].size();
    }

    for(unsigned int i = 0; i < mapThreads.size(); i++) {
        mapThreads[i].join();
    }
    auto emplacingEnd = std::chrono::high_resolution_clock::now();
    auto verticesMergeStart = std::chrono::high_resolution_clock::now();
    for(unsigned int i = 0; i < chunkLocalVertices.size(); i++) {
        vertices.insert(vertices.end(), chunkLocalVertices[i].begin(), chunkLocalVertices[i].end());
    }
    auto verticesMergeEnd = std::chrono::high_resolution_clock::now();
    auto mergingStart = std::chrono::high_resolution_clock::now();
    tbb::parallel_for(size_t(0), chunkLocalVertexMaps.size(), [&](size_t i) {
        for(const auto& [key, value] : chunkLocalVertexMaps[i]) {
            tbb::concurrent_hash_map<vec3, unsigned int, Vec3Hasher>::accessor accessor;
            vertexMap.insert(accessor, key);
            accessor->second = value;
        }
    });
    /*for(unsigned int i = 0; i < chunkLocalVertexMaps.size(); i++) {
        vertexMap.insert(chunkLocalVertexMaps[i].begin(), chunkLocalVertexMaps[i].end());
    }*/
    auto mergingEnd = std::chrono::high_resolution_clock::now();
    auto mergingDuration = std::chrono::duration_cast<std::chrono::microseconds>(mergingEnd - mergingStart).count();
    auto emplacingDuration = std::chrono::duration_cast<std::chrono::microseconds>(emplacingEnd - emplacingStart).count();
    auto verticesDuration = std::chrono::duration_cast<std::chrono::microseconds>(verticesEnd - verticesStart).count();
    auto verticesMergeDuration = std::chrono::duration_cast<std::chrono::microseconds>(verticesMergeEnd - verticesMergeStart).count();
    std::cout << "vertices merge duration: " << verticesMergeDuration << ", vertex map merging duration: " << mergingDuration << ", vertexMap addition duration: " << emplacingDuration << ", adding vertices duration: " << verticesDuration << std::endl;

    //auto batchStart = std::chrono::high_resolution_clock::now();
    //vertexMap.insert(std::make_move_iterator(tempVertexMap.begin()), std::make_move_iterator(tempVertexMap.end()));
    // After the loops, perform a single insertion
    //vertexMap.insert(tempVertexMap.begin(), tempVertexMap.end()); // apparently adding to the map is very slow
    //auto batchEnd = std::chrono::high_resolution_clock::now();
    //vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());
    
    /*auto batchDuration = std::chrono::duration_cast<std::chrono::microseconds>(batchEnd - batchStart).count();
    std::cout << "batch insertion duration: " << batchDuration << std::endl;*/

    
    
    /*// Step 2: Insert all at once into vertexMap
    for (const auto& [vertex, index] : tempVertices) {
        vertexMap.emplace(vertex, index);
    }*/

    //auto meshStart = std::chrono::high_resolution_clock::now();
    vboManager.FinalizeMesh(vertices.size());
    /*auto meshEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd - meshStart).count();
    std::cout << "vbo finalize mesh duration: " << totalDuration << std::endl;
    std::cout << "number of vertices: " << vertices.size() << std::endl;*/

    auto indicesStart = std::chrono::high_resolution_clock::now();
    for(unsigned int yi = 0; yi < gridHalfSideLength*2; yi++) {
        for(unsigned int zi = 0; zi < gridHalfSideLength*2; zi++) {
            for(unsigned int xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = gridX - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = gridY - gridHalfSideLength + yi;
                unsigned int currentChunkZ = gridZ - gridHalfSideLength + zi;
                /*if(gridX == 0) {
                    std::cout << "gridX is zero" << " currentChunkX: " << currentChunkX << std::endl;
                }
                if(gridY == 0) {
                    std::cout << "gridY is zero" << " currentChunkY: " << currentChunkY << std::endl;
                }
                if(gridZ == 0) {
                    std::cout << "gridZ is zero" << " currentChunkZ: " << currentChunkZ << std::endl;
                }*/

                if(meshedChunks.find(vec3(currentChunkX, currentChunkY, currentChunkZ)) != meshedChunks.end()) {
                    if(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].meshedPreviously) {
                        chunksToRender.push_back(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)]);
                        continue;
                    }
                }

                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboStartIndex = indices.size();
                for(unsigned int cubeY = 0; cubeY < chunkSize; cubeY++) {
                    for(unsigned int cubeZ = 0; cubeZ < chunkSize; cubeZ++) {
                        for(unsigned int cubeX = 0; cubeX < chunkSize; cubeX++) {
                            if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + cubeY*chunkSize*chunkSize + cubeZ*chunkSize + cubeX]) {
                                unsigned int baseX = currentChunkX*chunkSize + cubeX;
                                unsigned int baseY = currentChunkY*chunkSize + cubeY;
                                unsigned int baseZ = currentChunkZ*chunkSize + cubeZ;
                                unsigned int voxelX = xi*chunkSize + cubeX;
                                unsigned int voxelY = yi*chunkSize + cubeY;
                                unsigned int voxelZ = zi*chunkSize + cubeZ;
                                int faceVisible = 0;

                                if(baseZ > 0) {
                                    if(voxelZ > 0) {
                                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY, voxelZ-1)] == 0) faceVisible = 1;
                                    } else {
                                        faceVisible = 1; // will draw some unnecessary faces
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
                                // Function to get index from vertexMap
                                auto getIndex = [&](const vec3& vertex) {
                                    tbb::concurrent_hash_map<vec3, unsigned int, Vec3Hasher>::accessor accessor;
                                    if (vertexMap.find(accessor, vertex)) {
                                        return accessor->second; // Safely access the value
                                    }
                                    // Handle case where vertex is not found (return an invalid index, or throw an error)
                                    return (unsigned int)0; // Example error value
                                };
                                if(faceVisible) {
                                    // Front face
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX, baseY + 1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                                }
                                faceVisible = 0;
                                
                                if(voxelY < gridHalfSideLength*2*chunkSize-1) {
                                    if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY+1, voxelZ)] == 0) faceVisible = 1;
                                } else {
                                    faceVisible = 1;
                                    /*if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY+1, baseZ)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY+1, baseZ)) == 0) {
                                            faceVisible = 1;
                                        }
                                    } else {
                                        if(generator.GetBlockType(baseX, baseY+1, baseZ) == 0) { // if baseZ is 0 it's the edge of the world and we will never see the face anyway
                                            faceVisible = 1;
                                        }
                                    }*/
                                }
                                if(faceVisible) {
                                    // Top Face
                                    indices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY + 1, baseZ+1))); // baseY could be 31
                                    indices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY+1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                                }
                                faceVisible = 0;
                                
                                if(baseY > 0) {
                                    if(voxelY > 0) {
                                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY-1, voxelZ)] == 0) faceVisible = 1;
                                    } else {
                                        faceVisible = 1;
                                    }
                                }
                                if(faceVisible) {
                                     // Bottom face
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                                }
                                faceVisible = 0;

                                if(voxelZ < gridHalfSideLength*2*chunkSize-1) {
                                    if(voxels[ConvertToVoxelMapRelativeIndex(voxelX, voxelY, voxelZ+1)] == 0) faceVisible = 1;
                                } else {
                                    faceVisible = 1;
                                }

                                if(faceVisible) {
                                    // Back face
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY+1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ+1)));
                                }
                                faceVisible = 0;
                                
                                if(voxelX < gridHalfSideLength*2*chunkSize-1) {
                                    if(voxels[ConvertToVoxelMapRelativeIndex(voxelX+1, voxelY, voxelZ)] == 0) faceVisible = 1;
                                } else {
                                    faceVisible = 1;
                                }

                                if(faceVisible) {
                                    // Right face
                                    indices.push_back(getIndex(vec3(baseX+1, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY+1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX+1, baseY+1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX + 1, baseY + 1, baseZ)));
                                }
                                faceVisible = 0;

                                if(baseX > 0) {
                                    if(voxelX > 0) {
                                        if(voxels[ConvertToVoxelMapRelativeIndex(voxelX-1, voxelY, voxelZ)] == 0) faceVisible = 1;
                                    } else {
                                        faceVisible = 1;
                                    }
                                }

                                if(faceVisible) {
                                    // Left face
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX, baseY+1, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ+1)));
                                    indices.push_back(getIndex(vec3(baseX, baseY, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX, baseY+1, baseZ)));
                                    indices.push_back(getIndex(vec3(baseX, baseY + 1, baseZ+1)));
                                }
                                   
                            }
                            //indices.push_back() add indices
                        }
                    }
                }
                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboEndIndex = indices.size();

                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].meshedPreviously = 1;

                if(chunksToRender.size() > 0) {
                    if(chunksToRender[chunksToRender.size()-1].iboEndIndex == meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboStartIndex) {
                        chunksToRender[chunksToRender.size()-1].iboEndIndex = meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].iboEndIndex;
                        continue;
                    }
                    chunksToRender.push_back(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)]);
                    continue;
                }
                chunksToRender.push_back(meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)]);
            }
        }
    }
    auto indicesEnd = std::chrono::high_resolution_clock::now();
    auto indicesDuration = std::chrono::duration_cast<std::chrono::microseconds>(indicesEnd - indicesStart).count();
    auto agreggateDuration = std::chrono::duration_cast<std::chrono::microseconds>(indicesEnd - verticesStart).count();
    std::cout << "adding indices duration: " << indicesDuration << std::endl;
    std::cout << "total duration: " << agreggateDuration << std::endl;

    //auto meshStart2 = std::chrono::high_resolution_clock::now();
    iboManager.FinalizeMesh(indices.size());
    /*auto meshEnd2 = std::chrono::high_resolution_clock::now();

    auto totalDuration2 = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd2 - meshStart2).count();
    std::cout << "ibo finalize mesh duration: " << totalDuration2 << std::endl;
    std::cout << "number of indices: " << indices.size() << std::endl;*/
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