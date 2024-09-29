#include <ma_LogicalDevice.h>
#include <ma_UtilityFunctions.h>
#include <ma_Instance.h>
#include <set>

Mineanarchy::LogicalDevice::LogicalDevice(Instance* inst) : instance(inst) {

}

void Mineanarchy::LogicalDevice::createLogicalDevice(VkQueue* pQueue, VkQueue* gQueue) {
    Instance::QueueFamilyIndices indices = instance->findQueueFamilies();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instance->deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = instance->deviceExtensions.data();

    if (instance->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(instance->validationLayers.size());
        createInfo.ppEnabledLayerNames = instance->validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    instance->createLogicalDevice(&device, &createInfo);

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, gQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, pQueue);
}

void Mineanarchy::LogicalDevice::destroy() {
    vkDestroyDevice(device, nullptr);
}