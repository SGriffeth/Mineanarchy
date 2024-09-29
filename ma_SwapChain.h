#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <ma_Instance.h>

namespace Mineanarchy {
    class SwapChain {
        private:
        VkDevice logDevice;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        // Mark the copy constructor as deleted
        SwapChain(const SwapChain&) = delete;
        // Mark the copy assignment operator as deleted
        SwapChain& operator=(const SwapChain&) = delete;

        VkExtent2D chooseSwapExtent(Instance& instance, const VkSurfaceCapabilitiesKHR& capabilities);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        public:
        SwapChain(VkDevice logDevice);
        VkFormat getImageFormat();
        void createImageViews();
        void createSwapChain(Instance& instance);
        void createFramebuffers(VkRenderPass renderPass);

        friend void Instance::initVulkan();
    };
}