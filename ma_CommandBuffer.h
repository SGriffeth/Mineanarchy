#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>

class CommandPool;

class CommandBuffer {
    private:
    VkCommandBuffer commandBuffer;
    CommandPool* commandPool;
    public:
    CommandBuffer(CommandPool* pool);
    void createCommandBuffer();

    friend void Instance::initVulkan();
};