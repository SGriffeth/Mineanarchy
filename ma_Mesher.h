#include <ma_VoxelVertex.h>
#include <vector>
#include <ma_VisibleChunkGrid.h>
#include <ma_IndexBufferManager.h>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_vector.h>

namespace Mineanarchy {
    class Mesher {
        public:
        struct ChunkInfo {
            unsigned int iboStartIndex;
            unsigned int iboEndIndex;
            //unsigned int vboStartIndex;
            //unsigned int vboEndIndex;
            int meshedPreviously;
            ChunkInfo() {

            }
            /*ChunkInfo(unsigned int index) : vboStartIndex(index) {

            }*/
        };
        
        struct vec3 {
            unsigned int x, y, z;
            vec3(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z) {

            }
            vec3() : x(0), y(0), z(0) {

            }
            /*// Copy constructor
            vec3(const vec3& other) : x(other.x), y(other.y), z(other.z) {}

            // Optionally, you can also define a move constructor if needed
            vec3(vec3&& other) noexcept : x(other.x), y(other.y), z(other.z) {
                // Optionally set other to a safe state if needed
            }*/
            bool operator==(const vec3& other) const {
                return x == other.x && y == other.y && z == other.z;
            }
        };
        struct Vec3Hasher {
            size_t operator()(const vec3& v) const {
                return std::hash<unsigned int>()(v.x) ^ std::hash<unsigned int>()(v.y) ^ std::hash<unsigned int>()(v.z);
            }

            // Add a hash method to satisfy TBB's requirements
            size_t hash(const vec3& key) const {
                return (*this)(key); // Call the operator() defined above
            }

            // Equality check
            bool equal(const vec3& lhs, const vec3& rhs) const {
                return lhs == rhs; // Use the existing operator== defined in vec3
            }
        };

        private:

        std::vector<std::thread> threads;
        std::vector<VoxelVertex>& vertices;
        std::vector<unsigned int>& indices;
        //unsigned int numberOfIndices = 0;
        unsigned int numberOfVertices = 0;
        unsigned int cubeSideLength;
        const TerrainGenerator& generator;
        const VisibleChunkGrid& visibleChunkGrid;
        IndexBufferManager& iboManager;
        IndexBufferManager& vboManager;
        

        std::unordered_map<vec3, ChunkInfo, Vec3Hasher> meshedChunks;
        std::mutex mapMutex; // Mutex for protecting access to vertexMap
        std::mutex verticesMutex; // Mutex for protecting access to vertexMap
        //std::unordered_map<vec3, unsigned int, Vec3Hasher> vertexMap;
        std::vector<ChunkInfo> chunksToRender;
        void CleanupUnusedIndices();
        unsigned int ConvertToVoxelMapRelativeIndex(unsigned int xi, unsigned int yi, unsigned int zi);
        //void ProcessChunk(unsigned currentChunkX, unsigned currentChunkY, unsigned currentChunkZ, std::vector<glm::vec3>& vertices);
        //void MergeChunk(std::vector<glm::vec3>& chunkLocalVertices, std::vector<std::pair<vec3, size_t>>& chunkLocalVertexMap);
        //void InsertVertices(const std::vector<std::pair<vec3, size_t>>& verticesToInsert);
        public:
        Mesher(std::vector<VoxelVertex>& vertices, std::vector<unsigned int>& indices, unsigned int cubeSideLength, const VisibleChunkGrid& visibleChunkGrid, const TerrainGenerator& terrainGenerator, IndexBufferManager& vboManager, IndexBufferManager& iboManager);
        //void Mesh();
        void ScheduleMeshTask();
        void MeshChunk(unsigned int x, unsigned int y, unsigned int z, std::vector<unsigned int>& chunkLocalIndices, std::vector<VoxelVertex>& chunkLocalVertices/*, std::unordered_map<vec3, unsigned int, Vec3Hasher>& vertexMap*/);
        void AwaitChunkMeshing();
        unsigned int getVertexCount();
        const std::vector<ChunkInfo>& GetChunksToRender() const;
        //unsigned int getIndexCount();
    };
}