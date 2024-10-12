#pragma once

namespace Mineanarchy {
    class TerrainGenerator {
        private:
        const unsigned int SEA_LEVEL = 13;
        public:
        unsigned char sampleVoxel(unsigned int x, unsigned int y, unsigned int z) const;
        TerrainGenerator(unsigned int SEA_LEVEL);
    };
}