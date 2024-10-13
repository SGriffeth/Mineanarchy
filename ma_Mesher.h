#include <ma_VoxelVertex.h>
#include <vector>
#include <ma_VisibleChunkGrid.h>

namespace Mineanarchy {
    class Mesher {
        private:
        VoxelVertex* vertices;
        unsigned int* indices;
        unsigned int numberOfIndices = 0;
        unsigned int numberOfVertices = 0;
        unsigned int cubeSideLength;
        unsigned int gridHalfSideLength;
        const VisibleChunkGrid& visibleChunkGrid;
        unsigned int ConvertToVoxelMapRelativeIndex(unsigned int xi, unsigned int yi, unsigned int zi);
        public:
        Mesher(VoxelVertex* vertices, unsigned int* indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid);
        void Mesh();
        unsigned int getVertexCount();
        unsigned int getIndexCount();
    };
}