#pragma once
#include <vulkan/vulkan.h>
#include <ma_Instance.h>

class LogicalDevice {
    private:
    VkDevice device;
    Instance* instance;

    // Mark the copy constructor as deleted
    LogicalDevice(const LogicalDevice&) = delete;
    // Mark the copy assignment operator as deleted
    LogicalDevice& operator=(const LogicalDevice&) = delete;
    public:
    LogicalDevice(Instance* instance);
    void createLogicalDevice(VkQueue* pQueue, VkQueue* gQueue);
    void destroy();

    friend void Instance::initVulkan();
};