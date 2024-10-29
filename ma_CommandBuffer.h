#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>

namespace Mineanarchy {
    class CommandPool;
}

namespace Mineanarchy {
    class CommandBuffer {
        private:
        VkCommandBuffer commandBuffer;
        CommandPool* commandPool;
        public:
        CommandBuffer();
        CommandBuffer(CommandPool* pool);
        void createCommandBuffer();

        friend void Instance::initVulkan();
    };
}