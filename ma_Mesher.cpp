#include <ma_Mesher.h>
#include <cstring>
#include <iostream>

Mineanarchy::Mesher::Mesher(VoxelVertex* vertices, unsigned int* indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid) : vertices(vertices), indices(indices), cubeSideLength(cubeSideLength), visibleChunkGrid(visibleChunkGrid) {

}

void Mineanarchy::Mesher::Mesh() {
    /*// Define the vertices of a cube
    const VoxelVertex cubeVertices[8] = {
        {{startingX + -0.5f, startingY + -0.5f, startingZ + -0.5f}}, // 0: Back bottom left
        {{ startingX + 0.5f, startingY + -0.5f, startingZ + -0.5f}}, // 1: Back bottom right
        {{ startingX + 0.5f,  startingY + 0.5f, startingZ + -0.5f}}, // 2: Back top right
        {{startingX + -0.5f,  startingY + 0.5f, startingZ + -0.5f}}, // 3: Back top left
        {{startingX + -0.5f, startingY + -0.5f,  startingZ + 0.5f}}, // 4: Front bottom left
        {{ startingX + 0.5f, startingY + -0.5f,  startingZ + 0.5f}}, // 5: Front bottom right
        {{ startingX + 0.5f,  startingY + 0.5f,  startingZ + 0.5f}}, // 6: Front top right
        {{startingX + -0.5f,  startingY + 0.5f,  startingZ + 0.5f}}  // 7: Front top left
    };

    // Define the indices for the cube (two triangles per face)
    const unsigned int cubeIndices[6] = {
        0, 1, 2, // Back face
        0, 2, 3, // Back face
        4, 5, 6, // Front face
        4, 6, 7, // Front face
        0, 4, 7, // Left face
        0, 7, 3, // Left face
        1, 2, 6, // Right face
        1, 6, 5, // Right face
        3, 2, 6, // Top face
        3, 6, 7, // Top face
        0, 1, 5, // Bottom face
        0, 5, 4  // Bottom face
    };

    memcpy(indices, cubeIndices, sizeof(cubeIndices));
    memcpy(vertices, cubeVertices, sizeof(cubeVertices));
    numberOfIndices = 6;
    numberOfVertices = 8;
*/
    /*for(unsigned int chunkY = 0; chunkY < gridHalfSideLength*2; chunkY++) {
        for(unsigned int chunkZ = 0; chunkZ < gridHalfSideLength*2; chunkZ++) {
            for(unsigned int chunkX = 0; chunkX < gridHalfSideLength*2; chunkX++) {

                for(size_t yi = 0; yi < chunkSize; yi++) {
                    for(size_t zi = 0; zi < chunkSize; zi++) {
                        for(size_t xi = 0; xi < chunkSize; xi++) {
                            vertices[numberOfVertices] = {{startingX + chunkX * chunkSize + xi, startingY + chunkY * chunkSize + yi, startingZ + chunkZ * chunkSize + zi}};
                            numberOfVertices += 1;
                            if(voxels[visibleChunkGrid.GetVoxelMapIndex(chunkX, chunkY, chunkZ) + xi + yi*chunkSize*chunkSize + zi*chunkSize]) {
                                // problem is indices
                            }
                        }
                    }
                }

            }
        }
    }*/

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
                if(voxels[visibleChunkGrid.GetVoxelMapIndex(xi/chunkSize, yi/chunkSize, zi/chunkSize) + (xi%chunkSize) + (yi%chunkSize)*chunkSize*chunkSize + (zi%chunkSize)*chunkSize]) { // problem's here: not accessing the voxels in the same way  
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
                    unsigned int baseIndex = (yi * gridHalfSideLength*2*chunkSize * gridHalfSideLength*2*chunkSize) + (zi * gridHalfSideLength*2*chunkSize) + xi;

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

                   /* // Back face done 
                    indices[numberOfIndices+0] = (baseIndex + sideLengthX);                 // Bottom right
                    indices[numberOfIndices+1] = (baseIndex + sideLengthX + sideLengthX*sideLengthZ + 1);                 // Top right
                    indices[numberOfIndices+2] = (baseIndex + sideLengthX + sideLengthX*sideLengthZ);    // Top left
                    indices[numberOfIndices+3] = (baseIndex + sideLengthX);                 // Bottom right
                    indices[numberOfIndices+4] = (baseIndex + sideLengthX + 1);    // Top left
                    indices[numberOfIndices+5] = (baseIndex + sideLengthX + sideLengthX*sideLengthZ + 1);     // Bottom left
                    numberOfIndices+=6;*/
/*
                    // Top face done?
                    indices[numberOfIndices+0] = (baseIndex + sideLengthX*sideLengthZ);         // Top left
                    indices[numberOfIndices+1] = (baseIndex + sideLengthX*sideLengthZ + 1);     // Top right
                    indices[numberOfIndices+2] = (baseIndex + sideLengthX*sideLengthZ + sideLengthX);     // Top back left
                    indices[numberOfIndices+3] = (baseIndex + sideLengthX*sideLengthZ + 1);         // Bottom left
                    indices[numberOfIndices+4] = (baseIndex + sideLengthX*sideLengthZ + 1 + sideLengthX);     // Top right
                    indices[numberOfIndices+5] = (baseIndex + sideLengthX*sideLengthZ + sideLengthX);     // Top left
                    numberOfIndices+=6;*/
/*
                    // Bottom face
                    indices[numberOfIndices+0] = (baseIndex);                       // Bottom left
                    indices[numberOfIndices+1] = (baseIndex + 1);                   // Bottom right
                    indices[numberOfIndices+2] = (baseIndex + sideLengthX + 1);     // Top right
                    indices[numberOfIndices+3] = (baseIndex);                       // Bottom left
                    indices[numberOfIndices+4] = (baseIndex + sideLengthX + 1);     // Top right
                    indices[numberOfIndices+5] = (baseIndex + sideLengthX);         // Top left
                    numberOfIndices+=6;

                    // Left face
                    indices[numberOfIndices+0] = (baseIndex);                       // Bottom left
                    indices[numberOfIndices+1] = (baseIndex + sideLengthX);         // Top left
                    indices[numberOfIndices+2] = (baseIndex + sideLengthX + 1);     // Top right
                    indices[numberOfIndices+3] = (baseIndex);                       // Bottom left
                    indices[numberOfIndices+4] = (baseIndex + sideLengthX + 1);     // Top right
                    indices[numberOfIndices+5] = (baseIndex + 1);                   // Bottom right
                    numberOfIndices+=6;                    

                    // Right face
                    indices[numberOfIndices+0] = (baseIndex + 1);                   // Bottom right
                    indices[numberOfIndices+1] = (baseIndex + sideLengthX + 2);     // Top right
                    indices[numberOfIndices+2] = (baseIndex + sideLengthX + 3);     // Top left
                    indices[numberOfIndices+3] = (baseIndex + 1);                   // Bottom right
                    indices[numberOfIndices+4] = (baseIndex + sideLengthX + 3);     // Top left
                    indices[numberOfIndices+5] = (baseIndex + 2);
                    numberOfIndices+=6;*/

                    /*if(yi != 0)
                    if(voxels[zi*sideLengthY*sideLengthX + (yi-1)*sideLengthX + xi] && zi < sideLengthZ-1) {
                        // Bottom face
                        indices[numberOfIndices] = numberOfVertices;
                        indices[numberOfIndices+1] = numberOfVertices+1;
                        indices[numberOfIndices+2] = numberOfVertices+1+sideLengthX; // adding sideLengthX advances the index one row in the positive z direction (back)
                        indices[numberOfIndices+3] = numberOfVertices;
                        indices[numberOfIndices+4] = numberOfVertices+1+sideLengthX;
                        indices[numberOfIndices+5] = numberOfVertices+sideLengthX;
                        numberOfIndices += 6;
                    }

                    if(yi < sideLengthY-1)
                    if(voxels[zi*sideLengthY*sideLengthX + (yi+1)*sideLengthX + xi] && zi < sideLengthZ-1) {
                        // Top face
                        indices[numberOfIndices] = numberOfVertices+sideLengthX*sideLengthZ; // adding sideLengthX*sideLengthZ advances one layer in the positive y direction (up)
                        indices[numberOfIndices+1] = numberOfVertices+sideLengthX*sideLengthZ+1;
                        indices[numberOfIndices+2] = numberOfVertices+sideLengthX*sideLengthZ+1+sideLengthX;
                        indices[numberOfIndices+3] = numberOfVertices+sideLengthX*sideLengthZ;
                        indices[numberOfIndices+4] = numberOfVertices+sideLengthX*sideLengthZ+1+sideLengthX;
                        indices[numberOfIndices+5] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX;
                        numberOfIndices += 6;
                    }

                    if(zi != 0)
                    if(voxels[(zi-1)*sideLengthY*sideLengthX + yi*sideLengthX + xi] && yi < sideLengthY-1) {
                        // Front face
                        indices[numberOfIndices] = numberOfVertices;
                        indices[numberOfIndices+1] = numberOfVertices+sideLengthX*sideLengthZ;
                        indices[numberOfIndices+2] = numberOfVertices+sideLengthX*sideLengthZ+1;
                        indices[numberOfIndices+3] = numberOfVertices;
                        indices[numberOfIndices+4] = numberOfVertices+sideLengthX*sideLengthZ+1;
                        indices[numberOfIndices+5] = numberOfVertices+1;
                        numberOfIndices += 6;
                    }

                    if(zi < sideLengthZ-1)
                    if(voxels[(zi+1)*sideLengthY*sideLengthX + yi*sideLengthX + xi] && yi < sideLengthY-1) {
                        // Back face 2,3,6
                        indices[numberOfIndices] = numberOfVertices+sideLengthX+1;
                        indices[numberOfIndices+1] = numberOfVertices+sideLengthX;
                        indices[numberOfIndices+2] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX+1;
                        indices[numberOfIndices+3] = numberOfVertices+sideLengthX;
                        indices[numberOfIndices+4] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX;
                        indices[numberOfIndices+5] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX+1;
                        numberOfIndices += 6;
                    }

                    if(xi != 0)
                    if(voxels[zi*sideLengthY*sideLengthX + yi*sideLengthX + (xi-1)] && zi < sideLengthZ-1 && yi < sideLengthY-1) {
                        // Left face
                        indices[numberOfIndices] = numberOfVertices;
                        indices[numberOfIndices+1] = numberOfVertices+sideLengthX*sideLengthZ;
                        indices[numberOfIndices+2] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX;
                        indices[numberOfIndices+3] = numberOfVertices;
                        indices[numberOfIndices+4] = numberOfVertices+sideLengthX*sideLengthZ+sideLengthX;
                        indices[numberOfIndices+5] = numberOfVertices+sideLengthX;
                        numberOfIndices += 6;
                    }

                    if(xi < sideLengthX-1)
                    if(voxels[zi*sideLengthY*sideLengthX + yi*sideLengthX + (xi-1)] && zi < sideLengthZ-1 && yi < sideLengthY-1) {
                        // Right face
                        indices[numberOfIndices] = numberOfVertices+1;
                        indices[numberOfIndices+1] = numberOfVertices+1+sideLengthX;
                        indices[numberOfIndices+2] = numberOfVertices+1+sideLengthX*sideLengthZ+sideLengthX;
                        indices[numberOfIndices+3] = numberOfVertices+1;
                        indices[numberOfIndices+4] = numberOfVertices+1+sideLengthX*sideLengthZ+sideLengthX;
                        indices[numberOfIndices+5] = numberOfVertices+1+sideLengthX*sideLengthZ;
                        numberOfIndices += 6;
                    }

                    vertices[numberOfVertices] = {{startingX + xi, startingY + yi, startingZ + zi}};

                    numberOfVertices += 1;*/
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