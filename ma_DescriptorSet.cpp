#include <ma_DescriptorSetLayout.h>
#include <ma_UtilityFunctions.h>

Mineanarchy::DescriptorSet::DescriptorSet(DescriptorSetLayout* layout) : layout(layout->descriptorSetLayout), device(layout->device) {}

void Mineanarchy::DescriptorSet::createDescriptorPool() {
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = 1; // Number of descriptor sets (in this case, we're only creating one)

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = 1; // Maximum number of descriptor sets that can be allocated from this pool
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }

    UtilityFunctions::addDeletor([&]() {
        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    });
}

void Mineanarchy::DescriptorSet::createDescriptorSet() {
    createDescriptorPool();
    VkDescriptorSetLayout layouts[] = { layout };

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = layouts;

    if (vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor set!");
    }

    UtilityFunctions::addDeletor([&]() {
        vkFreeDescriptorSets(device, descriptorPool, 1, &descriptorSet);
    });
}