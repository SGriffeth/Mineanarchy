#include <ma_TerrainGenerator.h>
#include <ma_VisibleChunkGrid.h>
#include <iostream>

Mineanarchy::TerrainGenerator::TerrainGenerator(unsigned int sea_level) : SEA_LEVEL(sea_level) {
    //noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

}

void Mineanarchy::TerrainGenerator::SetChunkGrid(const Mineanarchy::VisibleChunkGrid* visibleChunkGrid) {
    this->visibleChunkGrid = visibleChunkGrid;
    heightMap = new unsigned int[visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2*visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2];
}

void Mineanarchy::TerrainGenerator::sampleVoxel(unsigned int x, unsigned int y, unsigned int z) const {
    //std::cout << "sample voxel at " << x << ", " << y << ", " << z << std::endl;
    //std::cout << "result: " << (y > SEA_LEVEL ? 0 : 1) << std::endl;
    /*if((y > SEA_LEVEL ? 0 : 1) == 0) {
        std::cout << "oh oh is air: " << x << ", " << y << ", " << z << std::endl;
    }*/
    //heightMap[heightMapX + heightMapZ*visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2] = noise.GetNoise((float)x, (float)z);
    unsigned int gridX, gridY, gridZ;
    visibleChunkGrid->GetGridPosition(gridX, gridY, gridZ);
    unsigned int heightMapX = x - (gridX - visibleChunkGrid->getGridHalfSideLength()) * visibleChunkGrid->getChunkSize();
    unsigned int heightMapZ = z - (gridZ - visibleChunkGrid->getGridHalfSideLength()) * visibleChunkGrid->getChunkSize();

    heightMap[heightMapX + heightMapZ*visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2] = (unsigned int)((noise.GetNoise((float)x*.23f, (float)z*.19f)+1) * SEA_LEVEL);
    /*if(y < SEA_LEVEL) return 1;
    const siv::PerlinNoise perlin{ seed };
    return perlin.octave2D_01((x * 0.01), (z * 0.01), 4);*/
}

unsigned char Mineanarchy::TerrainGenerator::GetBlockType(unsigned int x, unsigned int y, unsigned int z) const {
    //std::cout << "sample voxel at " << x << ", " << y << ", " << z << std::endl;
    //std::cout << "result: " << (y > SEA_LEVEL ? 0 : 1) << std::endl;
    /*if((y > SEA_LEVEL ? 0 : 1) == 0) {
        std::cout << "oh oh is air: " << x << ", " << y << ", " << z << std::endl;
    }*/
    //heightMap[heightMapX + heightMapZ*visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2] = noise.GetNoise((float)x, (float)z);
    return ((unsigned int)((noise.GetNoise((float)x*.23f, (float)z*.19f)+1) * SEA_LEVEL)) > y ? 1 : 0;
    /*if(y < SEA_LEVEL) return 1;
    const siv::PerlinNoise perlin{ seed };
    return perlin.octave2D_01((x * 0.01), (z * 0.01), 4);*/
}

const unsigned int& Mineanarchy::TerrainGenerator::getHeightMap(unsigned int x, unsigned int z) const {
    unsigned int gridX, gridY, gridZ;
    visibleChunkGrid->GetGridPosition(gridX, gridY, gridZ);
    unsigned int heightMapX = x - (gridX - visibleChunkGrid->getGridHalfSideLength()) * visibleChunkGrid->getChunkSize();
    unsigned int heightMapZ = z - (gridZ - visibleChunkGrid->getGridHalfSideLength()) * visibleChunkGrid->getChunkSize();
    return heightMap[heightMapX + heightMapZ*visibleChunkGrid->getChunkSize()*visibleChunkGrid->getGridHalfSideLength()*2];
}

const unsigned int* Mineanarchy::TerrainGenerator::getHeightMap() const {
    return heightMap;
}