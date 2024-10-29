#include <ma_IndexBufferManager.h>
#include <algorithm>

Mineanarchy::IndexBufferManager::IndexBufferManager(unsigned int initialSize) : currentBufferSize(initialSize) {
    //historicalSizes.reserve(40);
    maxSize = minSize = currentBufferSize;
}

void Mineanarchy::IndexBufferManager::FinalizeMesh(unsigned int numberOfIndices) {
    if(numberOfIndices > maxSize) {
        maxSize = numberOfIndices;
    }
    if(numberOfIndices < minSize) {
        minSize = numberOfIndices;
    }
    // Decide by how much to increase bufferSize
    if(numberOfIndices >= currentBufferSize) {
        currentBufferSize = numberOfIndices + bufferGrowthAmount;
    } else { // Decide whether to reduce bufferSize
        if(numberOfIndices < minSize+(maxSize-minSize)/2-indexBufferExtraSpace) { // Makes sure that currentBufferSize will be at least 20 bigger than the actual numberOfIndices Don't want to reduce below halfway between minSize and maxSize
            currentBufferSize = std::min(currentBufferSize, minSize+(maxSize-minSize)/2);  // will set the buffer size to at least indexBufferExtraSpace more than the numberOfindices used and at most the current buffer size 
            /*
            if numberOfIndices is 20 behind the half way point between maxSize and minSize currentBufferSize will be set to the half way point for extra space in case more are added later on

            */
        } else {  // Otherwise we reduce it to numberOfIndices plus some extra amount but no more than the current b uffer size
            // numberOfIndices > minSize+(maxSize-minSize)/2-20
            currentBufferSize = numberOfIndices+indexBufferExtraSpace; // Will be at least minSize+(maxSize-minSize)/2+1
            // if numberOfIndices = minSize+(maxSize-minSize)/2-19 so numberOfIndices+20 = minSize+(maxSize-minSize)/2+1
            /*
            numberOfIndices is less than 20 behind half way point so we make space for 20 more than how many we are using in case we need more later on as long as this isnt more than the current size
            in this case the size will always be more than in the previous case at least 1 more
            */
        }
    }
    //historicalSizes.push_back(numberOfIndices);
}

unsigned int Mineanarchy::IndexBufferManager::GetRecBufferCapacity() {
    return currentBufferSize;
}