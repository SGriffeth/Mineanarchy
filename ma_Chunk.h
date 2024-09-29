#include <cstddef>

namespace Mineanarchy {
    class Chunk {
        private:
        uint x, y, z;
        std::byte voxelMap[32*32*32];
        void sampleBlock(uint x, uint y, uint z);
        public:
        Chunk(uint x, uint y, uint z);
    };
}