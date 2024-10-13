#include <ma_UtilityFunctions.h>
#include <ma_VisibleChunkGrid.h>
#include <cstring> // For C++
#include <fstream> // Includes both ifstream and ofstream
#include <string> // For std::string
#include <iostream>

Mineanarchy::VisibleChunkGrid::VisibleChunkGrid(const Mineanarchy::TerrainGenerator& generator, unsigned int chunkSize, unsigned int gridHalfSideLength) : chunkSize(chunkSize), gridHalfSideLength(gridHalfSideLength), generator(generator) {
    cachedChunkChanges = new PossiblyChangedVoxel[chunkSize*chunkSize*chunkSize]();
    voxelMap = new unsigned char[gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize]();
    std::cout << "voxel count: " << (gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize) << std::endl;
    previousVoxelMap = new unsigned char[gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize * gridHalfSideLength*2 * chunkSize]();
}

Mineanarchy::VisibleChunkGrid::~VisibleChunkGrid() {
    delete voxelMap;
    delete previousVoxelMap;
    delete cachedChunkChanges;
}

void Mineanarchy::VisibleChunkGrid::UpdateGridPosition(unsigned int x, unsigned int y, unsigned int z) {
    if(previousx == x && previousy == y && previousz == z) {
        return;
    }
    previousx = this->x;
    previousy = this->y;
    previousz = this->z;
    if(x < gridHalfSideLength) x = gridHalfSideLength;
    if(y < gridHalfSideLength) y = gridHalfSideLength;
    if(z < gridHalfSideLength) z = gridHalfSideLength;

    this->x = x;
    this->y = y;
    this->z = z;
    //std::cout << "y is " << y << std::endl;
    //std::cout << "initial index: " << GetVoxelMapIndex(0, 0, 0) << std::endl;
    for(size_t zi = 0; zi < gridHalfSideLength*2; zi++) {
        for(size_t yi = 0; yi < gridHalfSideLength*2; yi++) {
            for(size_t xi = 0; xi < gridHalfSideLength*2; xi++) {
                unsigned int currentChunkX = x - gridHalfSideLength + xi; // x,y, and z as in the grids current position
                unsigned int currentChunkY = y - gridHalfSideLength + yi;
                unsigned int currentChunkZ = z - gridHalfSideLength + zi;
                
                /*std::cout << "currentChunk: (" << currentChunkX << ", " << currentChunkY << ", " << currentChunkZ << ")" << std::endl;
                std::cout << "previous grid pos: (" << previousx << ", " << previousy << ", " << previousz << ")" << std::endl;
                std::cout << "grid half side length: " << gridHalfSideLength << std::endl;*/
                /*if(currentChunkX < previousx + gridHalfSideLength && currentChunkX > previousx - gridHalfSideLength) {
                    if(currentChunkY < previousy + gridHalfSideLength && currentChunkY > previousy - gridHalfSideLength) {
                        if(currentChunkZ < previousz + gridHalfSideLength && currentChunkZ > previousz - gridHalfSideLength) {
                            // This chunk was previously loaded (conditions never met for some reason)
                            int previousChunkX = static_cast<std::int32_t>(xi) + static_cast<std::int32_t>(this->x) - static_cast<std::int32_t>(previousx);
                            int previousChunkY = static_cast<std::int32_t>(yi) + static_cast<std::int32_t>(this->y) - static_cast<std::int32_t>(previousy);
                            int previousChunkZ = static_cast<std::int32_t>(zi) + static_cast<std::int32_t>(this->z) - static_cast<std::int32_t>(previousz);
                            if(previousChunkX < 0 || previousChunkY < 0 || previousChunkZ < 0) {
                                throw std::runtime_error("negative previous chunk exception");
                            }
                            memcpy(voxelMap+GetVoxelMapIndex(xi, yi, zi), previousVoxelMap+GetVoxelMapIndex(previousChunkX, previousChunkY, previousChunkZ), chunkSize*chunkSize*chunkSize);
                            memcpy(previousVoxelMap+GetVoxelMapIndex(xi, yi, zi), voxelMap+GetVoxelMapIndex(xi, yi, zi), chunkSize*chunkSize*chunkSize);
                            std::cout << "currently loaded chunk: (" << xi << ", " << yi << ", " << zi << ") previously loaded chunk: (" << previousChunkX << ", " << previousChunkY << ", " << previousChunkZ  << ") diff: (" << static_cast<std::int32_t>(this->x) - static_cast<std::int32_t>(previousx) << ", " << static_cast<std::int32_t>(this->y) - static_cast<std::int32_t>(previousy) << ". " << static_cast<std::int32_t>(this->z) - static_cast<std::int32_t>(previousz) << ")" << std::endl;
                            continue;
                        }
                    }
                }*/
                LoadChunkChangesFromFile(currentChunkX, currentChunkY, currentChunkZ);
                UpdateVisibleChunk(xi, yi, zi);
            }
        }
    }
    std::cout << "final index: " << (GetVoxelMapIndex(gridHalfSideLength*2-1, gridHalfSideLength*2-1, gridHalfSideLength*2-1) + (chunkSize-1) + (chunkSize-1)*chunkSize*chunkSize + (chunkSize-1)*chunkSize) << std::endl;
}

void Mineanarchy::VisibleChunkGrid::GetGridPosition(unsigned int& x, unsigned int& y, unsigned int& z) const {
    x = this->x;
    y = this->y;
    z = this->z;
}

// x, y, and z are relative chunk coordinates that is relative to the visible chunk grid
unsigned int Mineanarchy::VisibleChunkGrid::GetVoxelMapIndex(unsigned int x, unsigned int y, unsigned int z) const {
    unsigned int index;
    index = (x)*chunkSize*chunkSize*chunkSize + chunkSize*chunkSize*chunkSize*gridHalfSideLength*2*(z) + chunkSize*chunkSize*chunkSize*gridHalfSideLength*2*gridHalfSideLength*2*(y); // problem's here
    return index;
}

void Mineanarchy::VisibleChunkGrid::UpdateVisibleChunk(unsigned int x, unsigned int y, unsigned int z) {
    size_t chunkVoxelIndex = GetVoxelMapIndex(x, y, z);
    unsigned int currentChunkX = this->x - gridHalfSideLength + x;
    unsigned int currentChunkY = this->y - gridHalfSideLength + y;
    unsigned int currentChunkZ = this->z - gridHalfSideLength + z;

    const unsigned int* heightMap = generator.getHeightMap();

    for(unsigned int yi = 0; yi < chunkSize; yi++) {
        for(unsigned int zi = 0; zi < chunkSize; zi++) {
            for(unsigned int xi = 0; xi < chunkSize; xi++) {
                if(cachedChunkChanges[xi + yi*chunkSize*chunkSize + zi*chunkSize].hasBeenChanged) {
                    std::cout << "loading cached chunk change" << std::endl;
                }
                if(yi == 0) generator.sampleVoxel(currentChunkX*chunkSize + xi, 0, currentChunkZ*chunkSize + zi);
                /*voxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize] =
                cachedChunkChanges[xi + yi*chunkSize*chunkSize + zi*chunkSize].hasBeenChanged ? cachedChunkChanges[xi + yi*chunkSize*chunkSize + zi*chunkSize].blockId : (currentChunkY*chunkSize + yi < generator.getHeightMap(currentChunkX*chunkSize, currentChunkZ*chunkSize) ? 1 : 0);*/

                voxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize] = (currentChunkY*chunkSize + yi < generator.getHeightMap(currentChunkX*chunkSize, currentChunkZ*chunkSize) ? 1 : 0);

                //voxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize] = generator.sampleVoxel(currentChunkX*chunkSize + xi, currentChunkY*chunkSize + yi, currentChunkZ*chunkSize + zi);
                /*if(voxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize] == 0) { // Condition never met 
                    std::cout << (currentChunkY*chunkSize + yi) << " ";
                    //std::cout << "(" << xi << ", " << yi << ", " << zi << ") ";
                } else if((currentChunkY*chunkSize + yi) > 80) {
                    std::cout << "strange: " << currentChunkY*chunkSize + yi << std::endl;
                }*/
                //previousVoxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize] = voxelMap[chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize];
                //std::cout << "index: " << chunkVoxelIndex + xi + yi*chunkSize*chunkSize + zi*chunkSize << std::endl;
            }
        }
    }
    //std::cout << std::endl;
}

void Mineanarchy::VisibleChunkGrid::LoadChunkChangesFromFile(unsigned int x, unsigned int y, unsigned int z) {
    std::string gameDir;
    UtilityFunctions::getGameDirectory(gameDir);
    std::string filename = gameDir + "/chunks/chunk_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        //std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    Voxel voxel;
    while (file.read(reinterpret_cast<char*>(&voxel), sizeof(Voxel))) {
        cachedChunkChanges[voxel.x + voxel.y*chunkSize + voxel.z*chunkSize*chunkSize].blockId = voxel.blockId;
        cachedChunkChanges[voxel.x + voxel.y*chunkSize + voxel.z*chunkSize*chunkSize].hasBeenChanged = 1;
    }

    file.close();
}

void Mineanarchy::VisibleChunkGrid::SaveChunkChangesToFile(unsigned int x, unsigned int y, unsigned int z, const Voxel* voxels) const {
    std::string gameDir;
    UtilityFunctions::getGameDirectory(gameDir);
    std::string filename = gameDir + "/chunks/chunk_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(voxels), sizeof(Voxel) * chunkSize*chunkSize*chunkSize);
    file.close();
}

void Mineanarchy::VisibleChunkGrid::UpdateGridSideLength(unsigned int newHalfSideLength) {
    gridHalfSideLength = newHalfSideLength;
}

const unsigned char* Mineanarchy::VisibleChunkGrid::getVoxelData() const {
    return voxelMap;
}

unsigned int Mineanarchy::VisibleChunkGrid::getGridHalfSideLength() const {
    return gridHalfSideLength;
}

unsigned int Mineanarchy::VisibleChunkGrid::getChunkSize() const {
    return chunkSize;
}