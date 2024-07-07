#include <ma_Instance.h>
#include <ma_CommandPool.h>
#include <ma_UtilityFunctions.h>

CommandPool::CommandPool(VkDevice dev) : device(dev) {

}

void CommandPool::createCommandPool(Instance& instance) {
    Instance::QueueFamilyIndices queueFamilyIndices = instance.findQueueFamilies();

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &pool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }

    UtilityFunctions::addDeletor([=]() {
        vkDestroyCommandPool(device, pool, nullptr);
    });
}