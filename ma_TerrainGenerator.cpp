#include <ma_TerrainGenerator.h>
#include <iostream>

Mineanarchy::TerrainGenerator::TerrainGenerator(unsigned int sea_level) : SEA_LEVEL(sea_level) {

}

unsigned char Mineanarchy::TerrainGenerator::sampleVoxel(unsigned int x, unsigned int y, unsigned int z) const {
    //std::cout << "sample voxel at " << x << ", " << y << ", " << z << std::endl;
    //std::cout << "result: " << (y > SEA_LEVEL ? 0 : 1) << std::endl;
    /*if((y > SEA_LEVEL ? 0 : 1) == 0) {
        std::cout << "oh oh is air: " << x << ", " << y << ", " << z << std::endl;
    }*/
    return y > SEA_LEVEL ? 0 : 1;
}