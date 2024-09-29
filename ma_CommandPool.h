#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>
#include <ma_CommandBuffer.h>

namespace Mineanarchy {
    class Instance;
    class CommandPool {
        public:
        CommandPool(VkDevice device);
        void createCommandPool(Instance& instance);
        private:
        VkCommandPool pool;
        VkDevice device;

        friend void Instance::initVulkan();
        friend void CommandBuffer::createCommandBuffer();
    };
}