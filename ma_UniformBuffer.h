#pragma once
#include <vulkan/vulkan.h>

namespace Mineanarchy {
    class DescriptorSet;
    class UniformBuffer {
        private:
        VkDescriptorSet descriptorSet;
        size_t bufferSize;
        VkBuffer uniformBuffer;
        VkDevice device;
        VkDeviceMemory uniformBufferMemory;
        uint32_t findMemoryType(VkPhysicalDevice dev, uint32_t typeFilter, VkMemoryPropertyFlags properties);
        public:
        UniformBuffer(DescriptorSet& set, size_t size);
        void updateUniformBuffer(void*, VkWriteDescriptorSet);
        void createUniformBuffer(VkPhysicalDevice physicalDevice);
    };
}