#pragma once
#include <FastNoiseLite.h>
namespace Mineanarchy {
    class VisibleChunkGrid;
}

namespace Mineanarchy {
    class TerrainGenerator {
        private:
        const unsigned int SEA_LEVEL = 13;
        //const siv::PerlinNoise::seed_type seed = 123456u;
        FastNoiseLite noise;
        unsigned int* heightMap;
        const VisibleChunkGrid* visibleChunkGrid;
        public:
        void sampleVoxel(unsigned int x, unsigned int y, unsigned int z) const;
        unsigned char GetBlockType(unsigned int x, unsigned int y, unsigned int z) const;
        TerrainGenerator(unsigned int SEA_LEVEL);
        void SetChunkGrid(const VisibleChunkGrid* visibleChunkGrid);
        const unsigned int* getHeightMap() const;
        const unsigned int& getHeightMap(unsigned int x, unsigned int z) const;
    };
}