#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>
namespace Mineanarchy {
    class Buffer {
        public:
        Buffer(VkDevice dev, size_t bufferSize);
        void createBuffer(VkQueue graphicsQueue, VkCommandPool vkCommandPool, VkPhysicalDevice physicalDevice, void* vertices, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
        void updateBuffer(void* data);

        private:
        size_t bufferSize;
        VkBuffer buffer;
        VkDeviceMemory bufferMemory;
        VkDevice device;
        VkQueue graphicsQueue;
        VkPhysicalDevice physicalDevice;
        VkCommandPool commandPool;
        void createBuffer(VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkQueue graphicsQueue, VkCommandPool vkCommandPool, VkBuffer& srcBuffer, VkBuffer& dstBuffer, VkDeviceSize size);
        uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

        friend void Instance::initVulkan();
        friend void Instance::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    };
}