#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>
#include <ma_UniformBuffer.h>

class DescriptorSetLayout;

class DescriptorSet {
    private:
    VkDevice device;
    VkDescriptorSetLayout layout;
    DescriptorSetLayout* descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    void createDescriptorPool();
    public:
    void createDescriptorSet();

    DescriptorSet(DescriptorSetLayout* descriptorSetLayout);
    friend void Instance::initVulkan();
    friend UniformBuffer::UniformBuffer(DescriptorSet&, size_t);
};