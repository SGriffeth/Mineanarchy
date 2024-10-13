

#include <ma_Mesher.h>
#include <cstring>
#include <iostream>

Mineanarchy::Mesher::Mesher(VoxelVertex* vertices, unsigned int* indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid) : vertices(vertices), indices(indices), cubeSideLength(cubeSideLength), visibleChunkGrid(visibleChunkGrid) {

}

void Mineanarchy::Mesher::Mesh() {
    const unsigned char* voxels = visibleChunkGrid.getVoxelData();
    unsigned int chunkSize = visibleChunkGrid.getChunkSize();
    unsigned int gridHalfSideLength = visibleChunkGrid.getGridHalfSideLength();
    unsigned int startingX, startingY, startingZ;
    visibleChunkGrid.GetGridPosition(startingX, startingY, startingZ);
    startingX -= gridHalfSideLength;
    startingY -= gridHalfSideLength;
    startingZ -= gridHalfSideLength;
    startingX *= chunkSize;
    startingY *= chunkSize;
    startingZ *= chunkSize;
    numberOfIndices = 0;
    numberOfVertices = 0;
    for(size_t yi = 0; yi < gridHalfSideLength*2*chunkSize; yi++) {
        for(size_t zi = 0; zi < gridHalfSideLength*2*chunkSize; zi++) {
            for(size_t xi = 0; xi < gridHalfSideLength*2*chunkSize; xi++) {
                vertices[numberOfVertices] = {{startingX + xi, startingY + yi, startingZ + zi}};
                numberOfVertices += 1;
                if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi/chunkSize, yi/chunkSize, zi/chunkSize) + (xi%chunkSize) + (yi%chunkSize)*chunkSize*chunkSize + (zi%chunkSize)*chunkSize]) {
                    /*
                    // Bottom face
                    {{0, 0, 0}},  // Vertex 0: Bottom-left-front
                    {{1, 0, 0}},  // Vertex 1: Bottom-right-front
                    {{1, 0, 1}},  // Vertex 2: Bottom-right-back
                    {{0, 0, 1}},  // Vertex 3: Bottom-left-back

                    // Top face
                    {{0, 1, 0}},  // Vertex 4: Top-left-front
                    {{1, 1, 0}},  // Vertex 5: Top-right-front
                    {{1, 1, 1}},  // Vertex 6: Top-right-back
                    {{0, 1, 1}}   // Vertex 7: Top-left-back

                    // Bottom face
                    0, 1, 2, 0, 2, 3,
                    // Top face
                    4, 5, 6, 4, 6, 7,
                    // Front face
                    0, 4, 5, 0, 5, 1,
                    // Back face
                    3, 2, 6, 3, 6, 7,
                    // Left face
                    0, 3, 7, 0, 7, 4,
                    // Right face
                    1, 5, 6, 1, 6, 2
                    */
                    unsigned int baseIndex = (yi * gridHalfSideLength*2*chunkSize * gridHalfSideLength*2*chunkSize) + (zi * gridHalfSideLength*2*chunkSize) + xi; // no problem here because vertices aren't laid out in the same way as the voxels

                    if(yi < gridHalfSideLength*2*chunkSize-1 && xi < gridHalfSideLength*2*chunkSize-1) {
                        // Front face done
                        indices[numberOfIndices+0] = (baseIndex);                     // Bottom left
                        indices[numberOfIndices+1] = (baseIndex + gridHalfSideLength*2*chunkSize*gridHalfSideLength*2*chunkSize + 1);                 // Front top right
                        indices[numberOfIndices+2] = (baseIndex + gridHalfSideLength*2*chunkSize*gridHalfSideLength*2*chunkSize);    // Front top left
                        indices[numberOfIndices+3] = (baseIndex);                     // Bottom left
                        indices[numberOfIndices+4] = (baseIndex + 1);    // Bottom right
                        indices[numberOfIndices+5] = (baseIndex + gridHalfSideLength*2*chunkSize*gridHalfSideLength*2*chunkSize + 1);         // Front Top right
                        numberOfIndices+=6;
                    }
                }
            }
        }
    }
}

unsigned int Mineanarchy::Mesher::getIndexCount() {
    return numberOfIndices;
}

unsigned int Mineanarchy::Mesher::getVertexCount() {
    return numberOfVertices;
}