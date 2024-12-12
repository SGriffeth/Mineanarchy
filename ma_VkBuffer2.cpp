#include <ma_VkBuffer2.h>

Mineanarchy::Buffer::Buffer(VkDevice dev, size_t bufferSize) : device(dev), bufferSize(bufferSize) {

}

void Mineanarchy::Buffer::createBuffer(VkQueue graphicsQueue, VkCommandPool vkCommandPool, VkPhysicalDevice physicalDevice, void* vertices, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
    //VkDeviceSize bufferSize = sizeof(vertices[0]) * numVertices;
    this->graphicsQueue = graphicsQueue;
    this->physicalDevice = physicalDevice;
    this->commandPool = vkCommandPool;
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices, (size_t) bufferSize); // bufferSize is greater than vertices size causing segfault
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(physicalDevice, bufferSize, usage, properties, newBuffer, newBufferMemory);

    copyBuffer(stagingBuffer, newBuffer, bufferSize);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
     UtilityFunctions::addDeletor([&]() { // newBuffer eventually destroyed by resizeBuffer so this causes segfault after termination
        if(!firstResize) {
            vkFreeMemory(device, oldBufferMemory, nullptr);
            vkDestroyBuffer(device, oldBuffer, nullptr);
        }
        vkFreeMemory(device, newBufferMemory, nullptr);
        vkDestroyBuffer(device, newBuffer, nullptr);
    });
}

void Mineanarchy::Buffer::createBuffer(VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void Mineanarchy::Buffer::copyBuffer(VkBuffer& srcBuffer, VkBuffer& dstBuffer, VkDeviceSize size) {
    VkFence fence;
    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = 0;
    vkCreateFence(device, &fenceInfo, nullptr, &fence);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer command;
    vkAllocateCommandBuffers(device, &allocInfo, &command);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(command, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(command, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(command);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &command;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence);
    // Wait for the specific command buffer to finish executing
    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);

    vkFreeCommandBuffers(device, commandPool, 1, &command);
    
    // Clean up the fence
    vkDestroyFence(device, fence, nullptr);
}

uint32_t Mineanarchy::Buffer::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Mineanarchy::Buffer::updateBuffer(void* data2, size_t dataSize) {
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(physicalDevice, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, dataSize, 0, &data);
        memcpy(data, data2, (size_t) dataSize);
    vkUnmapMemory(device, stagingBufferMemory);

    copyBuffer(stagingBuffer, newBuffer, dataSize);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

// createBuffer(VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
// Resizing index buffer
void Mineanarchy::Buffer::resizeBuffer(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkDeviceSize newSize) {
    // 4. Cleanup the old buffer
    if(!firstResize) {
        vkDestroyBuffer(device, oldBuffer, nullptr);
        vkFreeMemory(device, oldBufferMemory, nullptr);
    }

    oldBuffer = newBuffer;
    oldBufferMemory = newBufferMemory;
    
    // 1. Create new buffer
    createBuffer(physicalDevice, newSize, usage, properties, newBuffer, newBufferMemory); // newBuffer is used in rendering always

    // 2. Copy old buffer data to new buffer
    //VkDeviceSize oldSize = bufferSize/* size of the old buffer */;

    // 3. Update your reference to the new buffer
    // (Handle this in your application logic)
    bufferSize = newSize;
    firstResize = 0;
}


/*void Mineanarchy::Buffer::destroy() {
    if(!firstResize) {
        vkFreeMemory(device, oldBufferMemory, nullptr);
        vkDestroyBuffer(device, oldBuffer, nullptr);
    }
    vkFreeMemory(device, newBufferMemory, nullptr);
    vkDestroyBuffer(device, newBuffer, nullptr);
}*/