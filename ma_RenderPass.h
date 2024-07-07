#pragma once
#include <vulkan/vulkan.h>

#include <ma_Instance.h>

class RenderPass {
    private:
    VkRenderPass renderPass;
    public:
    RenderPass() = default;
    void createRenderPass(VkDevice device, VkFormat imageFormat);

    RenderPass& operator=(const RenderPass&) = delete;
    RenderPass(const RenderPass&) = delete;

    friend void Instance::initVulkan();
};