#include <ma_VoxelVertex.h>
#include <vector>
#include <ma_VisibleChunkGrid.h>
#include <ma_IndexBufferManager.h>
#include <unordered_map>

namespace Mineanarchy {
    class Mesher {
        public:
        struct ChunkInfo {
            unsigned int iboStartIndex;
            unsigned int iboEndIndex;
            unsigned int vboStartIndex;
            unsigned int vboEndIndex;
            int meshedPreviously;
            ChunkInfo() {

            }
            ChunkInfo(unsigned int index) : vboStartIndex(index) {

            }
        };
        
        struct vec3 {
            unsigned int x, y, z;
            vec3(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z) {

            }
            vec3() : x(0), y(0), z(0) {

            }
            bool operator==(const vec3& other) const {
                return x == other.x && y == other.y && z == other.z;
            }
        };
        struct Vec3Hasher {
            size_t operator()(const vec3& v) const {
                return std::hash<unsigned int>()(v.x) ^ std::hash<unsigned int>()(v.y) ^ std::hash<unsigned int>()(v.z);
            }
        };

        private:

        std::vector<VoxelVertex>& vertices;
        std::vector<unsigned int>& indices;
        //unsigned int numberOfIndices = 0;
        unsigned int numberOfVertices = 0;
        unsigned int cubeSideLength;
        unsigned int gridHalfSideLength;
        const TerrainGenerator& generator;
        const VisibleChunkGrid& visibleChunkGrid;
        IndexBufferManager& iboManager;
        IndexBufferManager& vboManager;
        

        std::unordered_map<vec3, ChunkInfo, Vec3Hasher> meshedChunks;
        std::unordered_map<vec3, unsigned int, Vec3Hasher> vertexMap;
        std::vector<ChunkInfo> chunksToRender;
        void CleanupUnusedIndices();
        unsigned int ConvertToVoxelMapRelativeIndex(unsigned int xi, unsigned int yi, unsigned int zi);
        public:
        Mesher(std::vector<VoxelVertex>& vertices, std::vector<unsigned int>& indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid, const TerrainGenerator& terrainGenerator, IndexBufferManager& vboManager, IndexBufferManager& iboManager);
        void Mesh();
        unsigned int getVertexCount();
        const std::vector<ChunkInfo>& GetChunksToRender() const;
        //unsigned int getIndexCount();
    };
}