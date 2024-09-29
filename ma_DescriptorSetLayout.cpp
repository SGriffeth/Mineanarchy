#include <ma_DescriptorSetLayout.h>
#include <ma_UtilityFunctions.h>

Mineanarchy::DescriptorSetLayout::DescriptorSetLayout(VkDevice dev, VkDescriptorSetLayoutBinding uboLayoutBinding, VkDescriptorSetLayoutCreateInfo layoutInfo) : device(dev), uboLayoutBinding(uboLayoutBinding), layoutInfo(layoutInfo) {
    this->layoutInfo.pBindings = &this->uboLayoutBinding;
}

void Mineanarchy::DescriptorSetLayout::createDescriptorSetLayout() {
    if (vkCreateDescriptorSetLayout(device, &this->layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    UtilityFunctions::addDeletor([&]() {
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    });
}