#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <ma_Instance.h>

namespace Mineanarchy {
    class RenderPass;
    class GraphicsPipeline {
        public:
        GraphicsPipeline(VkDevice logDevice);
        void createGraphicsPipeline(const char* vertSpv, const char* fragSpv, std::vector<VkDescriptorSetLayout> layouts, VkRenderPass renderPass);
        VkShaderModule createShaderModule(const std::vector<char>& code);

        friend void Instance::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        private:
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkDevice logDevice;
        // Mark the copy constructor as deleted
        GraphicsPipeline(const GraphicsPipeline&) = delete;
        // Mark the copy assignment operator as deleted
        GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;
    };
}