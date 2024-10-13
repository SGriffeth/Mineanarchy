#pragma once
#include <cstddef>
#include <ma_TerrainGenerator.h>

namespace Mineanarchy {
    class VisibleChunkGrid {
        private:
        struct Voxel {
            unsigned int x;
            unsigned int y;
            unsigned int z;
            unsigned char blockId;
        };
        struct PossiblyChangedVoxel {
            unsigned char blockId;
            unsigned char hasBeenChanged;
        };
        const TerrainGenerator& generator;
        unsigned int previousx, previousy, previousz;
        unsigned int x, y, z;
        unsigned int gridHalfSideLength = 6;
        unsigned int chunkSize = 32;
        unsigned char* voxelMap;
        unsigned char* previousVoxelMap;
        PossiblyChangedVoxel* cachedChunkChanges;
        void SaveChunkChangesToFile(unsigned int x, unsigned int y, unsigned int z, const Voxel* voxels) const;
        void LoadChunkChangesFromFile(unsigned int x, unsigned int y, unsigned int z);
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

        // Delete move assignment operator
        VisibleChunkGrid& operator=(VisibleChunkGrid&&) noexcept = delete;
        void UpdateGridPosition(unsigned int x, unsigned int y, unsigned int z);
        
        void UpdateGridSideLength(unsigned int newHalfSideLength);

        void GetGridPosition(unsigned int& x, unsigned int& y, unsigned int& z) const;
        unsigned int GetVoxelMapIndex(unsigned int x, unsigned int y, unsigned int z) const;
        const unsigned char* getVoxelData() const;
        unsigned int getGridHalfSideLength() const;
        unsigned int getChunkSize() const;
    };
}