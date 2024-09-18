#include <ma_VkBuffer.h>
#include <cstring>
#include <ma_UtilityFunctions.h>
#include <iostream>

ma_VkBuffer::ma_VkBuffer(Instance* inst, size_t size) : bufferSize(size), instance(inst) {
    device = instance->device;
}

void ma_VkBuffer::createBuffer(void* vertexData, VkBufferUsageFlags flags, VkMemoryPropertyFlags memoryFlags) {
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    instance->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertexData, (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    instance->createBuffer(bufferSize, flags, memoryFlags, buffer, bufferMemory);

    instance->copyBuffer(stagingBuffer, buffer, bufferSize);
    UtilityFunctions::addDeletor([&]() {
        vkDestroyBuffer(device, buffer, nullptr);
        vkFreeMemory(device, bufferMemory, nullptr);
    });
}

void ma_VkBuffer::updateBuffer(void* vertexData) {
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    instance->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    if (stagingBufferMemory == VK_NULL_HANDLE) {
        // Handle error: memory object is not properly allocated
        std::cout << "memory object not properly allocated" << std::endl;
    }

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertexData, bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    instance->copyBuffer(stagingBuffer, buffer, bufferSize);
    
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}