#pragma once

namespace Mineanarchy {
    class IndexBufferManager {
        public:
        IndexBufferManager(unsigned int initialSize);
        unsigned int currentBufferSize;
        void FinalizeMesh(unsigned int numberOfIndices);
        unsigned int GetRecBufferCapacity();
        private:
        unsigned int bufferGrowthAmount = 240; // how much to increse the buffer by when the max historical size has been surpassed
        unsigned int indexBufferExtraSpace = 20;
        unsigned int maxSize, minSize;
        //std::vector<unsigned int> historicalSizes;
    };
}