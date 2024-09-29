#pragma once
#include <vulkan/vulkan.h>
#include <ma_DescriptorSet.h>
#include <vector>

namespace Mineanarchy {
    class DescriptorSetLayout {
        private:
        VkDevice device;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorSetLayoutBinding uboLayoutBinding;
        VkDescriptorSetLayoutCreateInfo layoutInfo;
        public:
        DescriptorSetLayout(VkDevice device, VkDescriptorSetLayoutBinding uboLayoutBinding, VkDescriptorSetLayoutCreateInfo layoutInfo);
        void createDescriptorSetLayout();

        friend DescriptorSet::DescriptorSet(DescriptorSetLayout*);
        friend void Instance::initVulkan();
    };
}