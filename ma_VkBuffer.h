#pragma once
#include <vulkan/vulkan.h>

class Mineanarchy::Instance;

namespace Mineanarchy {
    class ma_VkBuffer {
        private:
        size_t bufferSize;
        VkBuffer buffer;
        VkDeviceMemory bufferMemory;
        Instance* instance;
        VkDevice device;
        public:
        ma_VkBuffer(Instance* instance, size_t size);
        void createBuffer(void* data, VkBufferUsageFlags flags, VkMemoryPropertyFlags memoryFlags);
        void updateBuffer(void* data);
    };

    class Instance {
        public:
        // Other member functions and data members
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        private:
        VkDevice device;
        void initVulkan();
        friend ma_VkBuffer::ma_VkBuffer(Instance*, size_t);
    };
}