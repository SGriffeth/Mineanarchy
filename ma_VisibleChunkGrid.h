#pragma once
#include <cstddef>
#include <unordered_map>
#include <ma_TerrainGenerator.h>

namespace Mineanarchy {
    class VisibleChunkGrid {
        public:
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
        struct Voxel {
            unsigned int x;
            unsigned int y;
            unsigned int z;
            unsigned char blockId;
        };
        /*struct PossiblyChangedVoxel {
            unsigned char blockId;
            unsigned char hasBeenChanged;
        };*/
        const TerrainGenerator& generator;
        unsigned int previousx, previousy, previousz;
        unsigned int x, y, z;
        unsigned int gridHalfSideLength = 6;
        unsigned int chunkSize = 32;
        unsigned char* voxelMap;
        unsigned char* previousVoxelMap;
        std::unordered_map<vec3, unsigned int, Vec3Hasher> changedVoxels; // keeps track of which voxels have been changed
        //PossiblyChangedVoxel* cachedChunkChanges;
        //void SaveChunkChangesToFile(unsigned int x, unsigned int y, unsigned int z, const Voxel* voxels) const;
        //void LoadChunkChangesFromFile(unsigned int x, unsigned int y, unsigned int z);
        void UpdateVisibleChunk(unsigned int x, unsigned int y, unsigned int z);

        public:
        VisibleChunkGrid(const TerrainGenerator& generator, unsigned int chunkSize, unsigned int gridHalfSideLength);
        ~VisibleChunkGrid();
        // Delete copy constructor
        VisibleChunkGrid(const VisibleChunkGrid&) = delete;

        // Delete copy assignment operator
        VisibleChunkGrid& operator=(const VisibleChunkGrid&) = delete;

        // Delete move constructor
        VisibleChunkGrid(VisibleChunkGrid&&) noexcept = delete;

        void UpdateVoxel(vec3 coords, unsigned int blockState); // Writes the change to the corresponding chunk file and updates changedVoxels
        const std::unordered_map<vec3, unsigned int, Vec3Hasher>& GetChangedVoxels() const;

        // Delete move assignment operator
        VisibleChunkGrid& operator=(VisibleChunkGrid&&) noexcept = delete;
        void UpdateGridPosition(unsigned int x, unsigned int y, unsigned int z);
        
        void UpdateGridSideLength(unsigned int newHalfSideLength);

        void GetGridPosition(unsigned int& x, unsigned int& y, unsigned int& z) const;
        void GetPrevGridPosition(unsigned int& x, unsigned int& y, unsigned int& z) const;
        unsigned int GetVoxelMapIndex(unsigned int x, unsigned int y, unsigned int z) const;
        const unsigned char* getVoxelData() const;
        unsigned int getGridHalfSideLength() const;
        unsigned int getChunkSize() const;

        unsigned char GetVoxel(unsigned int x, unsigned int y, unsigned int z) const;
    };
}