#include <ma_Mesher.h>
#include <cstring>
#include <iostream>
#include <chrono>

Mineanarchy::Mesher::Mesher(std::vector<VoxelVertex>& vertices, std::vector<unsigned int>& indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid, const TerrainGenerator& terrainGenerator, IndexBufferManager& vboManager, IndexBufferManager& iboManager) : vertices(vertices), indices(indices), cubeSideLength(cubeSideLength), visibleChunkGrid(visibleChunkGrid), generator(terrainGenerator), vboManager(vboManager), iboManager(iboManager) {
    auto meshStart = std::chrono::high_resolution_clock::now();
    meshedChunks.reserve(2000000);
    vertices.reserve(2000000);
    indices.reserve(2000000); // doesn't take long
    auto meshEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd - meshStart).count();
    std::cout << "pre alloc vertex and index buffer duration: " << totalDuration << std::endl;
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
    chunksToRender.clear();
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

                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)] = ChunkInfo(vertices.size());
                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].meshedPreviously = 0;
                for(unsigned int cubeY = 0; cubeY < chunkSize+1; cubeY++) {
                    for(unsigned int cubeZ = 0; cubeZ < chunkSize+1; cubeZ++) {
                        for(unsigned int cubeX = 0; cubeX < chunkSize+1; cubeX++) {
                            vec3 vertex = vec3(currentChunkX*chunkSize + cubeX, currentChunkY*chunkSize + cubeY, currentChunkZ*chunkSize + cubeZ);
                            vertices.push_back(VoxelVertex(glm::vec3(vertex.x, vertex.y, vertex.z)));
                            vertexMap[vertex] = vertices.size()-1;
                        }
                    }
                }
                meshedChunks[vec3(currentChunkX, currentChunkY, currentChunkZ)].vboEndIndex = vertices.size();
            }
        }
    }
    vboManager.FinalizeMesh(vertices.size());
    std::cout << "number of vertices: " << vertices.size() << std::endl;

    for(unsigned int yi = 0; yi < gridHalfSideLength*2; yi++) {
        for(unsigned int zi = 0; zi < gridHalfSideLength*2; zi++) {
            for(unsigned int xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = gridX - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = gridY - gridHalfSideLength + yi;
                unsigned int currentChunkZ = gridZ - gridHalfSideLength + zi;
                if(gridX == 0) {
                    std::cout << "gridX is zero" << " currentChunkX: " << currentChunkX << std::endl;
                }
                if(gridY == 0) {
                    std::cout << "gridY is zero" << " currentChunkY: " << currentChunkY << std::endl;
                }
                if(gridZ == 0) {
                    std::cout << "gridZ is zero" << " currentChunkZ: " << currentChunkZ << std::endl;
                }

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
                                int faceVisible = 0;
                                if(cubeZ <= 0 && zi <= 0) {
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY, baseZ-1)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY, baseZ-1)) == 0) {
                                            // Front face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    } else {
                                        if(baseZ > 0)
                                        if(generator.GetBlockType(baseX, baseY, baseZ-1) == 0) { // if baseZ is 0 it's the edge of the world and we will never see the face anyway
                                            // Front face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    }
                                } else {
                                    if(cubeZ > 0) {
                                    if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + cubeY*chunkSize*chunkSize + (cubeZ-1)*chunkSize + cubeX] == 0) {
                                        //std::cout << "Front face reached" << std::endl;
                                        // Front face
                                        indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                        indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ)]);
                                        indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                        indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                        indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                    }
                                    } else {
                                        if(zi > 0)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi-1) + cubeY*chunkSize*chunkSize + (chunkSize-1)*chunkSize + cubeX] == 0) {
                                            // Front face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    }
                                }
                                
                                if(cubeY >= chunkSize-1 && yi >= gridHalfSideLength*2-1) { // We don't know whether the voxel above is solid or not so we can't decide whether to draw face so just set it to visible
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY+1, baseZ)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY+1, baseZ)) == 0) {
                                            faceVisible = 1;
                                        }
                                    } else {
                                        if(generator.GetBlockType(baseX, baseY+1, baseZ) == 0) {
                                            faceVisible = 1;
                                        }
                                    }
                                } else {
                                    if(cubeY < chunkSize-1) {
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + (cubeY+1)*chunkSize*chunkSize + (cubeZ)*chunkSize + cubeX] == 0) {
                                            faceVisible = 1;
                                        }
                                    } else {
                                        if(yi < gridHalfSideLength*2-1)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi+1, zi) + (0)*chunkSize*chunkSize + (cubeZ)*chunkSize + cubeX] == 0) {
                                            faceVisible = 1;
                                        }
                                    }
                                }
                                

                                if(faceVisible) {
                                    // Top Face
                                    indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                    indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]); // baseY could be 31
                                    indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                }
                                // Top Face
                                    /*indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                    indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]);
                                    indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY+1, baseZ)]);
                                    indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);*/
                                if(cubeY <= 0 && yi <= 0) {
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY-1, baseZ)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY-1, baseZ)) == 0) {
                                            // Bottom face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                        }
                                    } else {
                                        if(baseY > 0)
                                        if(generator.GetBlockType(baseX, baseY-1, baseZ) == 0) { // if baseY is 0 it's the end of the world and we will never see the block from under so we don't need the face rendered
                                            // Bottom face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                        }
                                    }
                                } else {
                                    if(cubeY > 0) {
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + (cubeY-1)*chunkSize*chunkSize + cubeZ*chunkSize + cubeX] == 0) {
                                            // Bottom face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                        }
                                    } else {
                                        if(yi > 0)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi-1, zi) + (chunkSize-1)*chunkSize*chunkSize + cubeZ*chunkSize + cubeX] == 0) {
                                            // Bottom face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                        }
                                    }
                                }

                                if(cubeZ >= chunkSize-1 && zi >= gridHalfSideLength*2-1) {
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX, baseY, baseZ+1)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX, baseY, baseZ+1)) == 0) {
                                            // Back face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                        }
                                    } else {
                                        if(generator.GetBlockType(baseX, baseY, baseZ+1) == 0) {
                                            // Back face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                        }
                                    }
                                } else {
                                    if(cubeZ < chunkSize-1) {
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + (cubeY)*chunkSize*chunkSize + (cubeZ+1)*chunkSize + cubeX] == 0) {
                                            // Back face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                        }
                                    } else {
                                        if(zi < gridHalfSideLength*2-1)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi+1) + cubeY*chunkSize*chunkSize + (0)*chunkSize + cubeX] == 0) {
                                            // Back face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ+1)]);
                                        }
                                    }
                                }
                                
                                if(cubeX >= chunkSize-1 && xi >= gridHalfSideLength*2-1) {
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX+1, baseY, baseZ)) != changedVoxels.end()) {
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX+1, baseY, baseZ)) == 0) {
                                            // Right face
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    } else {
                                        if(generator.GetBlockType(baseX+1, baseY, baseZ) == 0) {
                                            // Right face
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    }
                                } else {
                                    if(cubeX < chunkSize-1) {
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + cubeY*chunkSize*chunkSize + cubeZ*chunkSize + (cubeX+1)] == 0) {
                                            // Right face
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    } else {
                                        if(xi < gridHalfSideLength*2-1)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi+1, yi, zi) + cubeY*chunkSize*chunkSize + cubeZ*chunkSize + (0)] == 0) {
                                            // Right face
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX+1, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX + 1, baseY + 1, baseZ)]);
                                        }
                                    }
                                }

                                if(cubeX <= 0 && xi <= 0) {
                                    if(changedVoxels.find(VisibleChunkGrid::vec3(baseX-1, baseY, baseZ)) != changedVoxels.end()) { // beware when baseX is 0... todo: fix in future
                                        if(changedVoxels.at(VisibleChunkGrid::vec3(baseX-1, baseY, baseZ)) == 0) {
                                            // Left face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]);
                                        }
                                    } else {
                                        if(baseX > 0)
                                        if(generator.GetBlockType(baseX-1, baseY, baseZ) == 0) {
                                            // Left face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]);
                                        }
                                    }
                                } else {
                                    if(cubeX > 0) {
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi, yi, zi) + cubeY*chunkSize*chunkSize + cubeZ*chunkSize + (cubeX-1)] == 0) {
                                            //std::cout << "Left face reached" << std::endl;
                                            // Left face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]);
                                        }
                                    } else {
                                        if(xi > 0)
                                        if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi-1, yi, zi) + cubeY*chunkSize*chunkSize + cubeZ*chunkSize + (chunkSize-1)] == 0) {
                                        // std::cout << "Left face reached" << std::endl;
                                            // Left face
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ+1)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY+1, baseZ)]);
                                            indices.push_back(vertexMap[vec3(baseX, baseY + 1, baseZ+1)]);
                                        }
                                    }
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
    iboManager.FinalizeMesh(indices.size());
    std::cout << "number of indices: " << indices.size() << std::endl;
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