#include <ma_DescriptorSet.h>
#include <stdexcept>

UniformBuffer::UniformBuffer(DescriptorSet& set, size_t size) : bufferSize(size) {
    descriptorSet = set.descriptorSet;
    device = set.device;
}

void UniformBuffer::createUniformBuffer(VkPhysicalDevice physicalDevice) {
    // Create the buffer
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    vkCreateBuffer(device, &bufferInfo, nullptr, &uniformBuffer);

    // Allocate memory for the buffer
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, uniformBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    vkAllocateMemory(device, &allocInfo, nullptr, &uniformBufferMemory);

    // Bind the allocated memory to the buffer
    vkBindBufferMemory(device, uniformBuffer, uniformBufferMemory, 0);

    UtilityFunctions::addDeletor([&]() {
        // Destroy the Vulkan buffer object
        vkDestroyBuffer(device, uniformBuffer, nullptr);

        // Free the Vulkan device memory associated with the buffer
        vkFreeMemory(device, uniformBufferMemory, nullptr);
    });
}

void UniformBuffer::updateUniformBuffer(void* uboData, VkWriteDescriptorSet descriptorWrite) {
    void* data;
    vkMapMemory(device, uniformBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, uboData, bufferSize);
    vkUnmapMemory(device, uniformBufferMemory);


    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uniformBuffer; // The uniform buffer to bind
    bufferInfo.offset = 0; // Offset into the buffer (if necessary)
    bufferInfo.range = bufferSize; // Size of the buffer range

    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
}

uint32_t UniformBuffer::findMemoryType(VkPhysicalDevice dev, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(dev, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}