#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <functional>
#include <stack>
#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

class UtilityFunctions {
    public:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    static void addDeletor(std::function<void()> deletor);
    static void runDeletors();
    static bool readFile(const std::string& filename, std::vector<char>& buffer);
    static int queryConfigState();
    static void createConfig();
    static void getConfig();
    static void getGameDirectory(std::string& gameDir);
    static std::string getConfigValue(const char* name);
    static void setGameDirectory(const char* name);
    static void setMeshFile(const char* name);
    static void setSkeletonFile(const char* name);
    static void setAnimationFile(const char* name);
    static void writeToConfig();
    static const int CONFIG_INEXISTENT = 2;
    static const int CONFIG_INVALIDLY_FORMATTED = 1;
    static const int CONFIG_READABLE = 0; 
    static const char* CONFIG_NAME;
    private:
    static nlohmann::json config;
    static std::filesystem::path gameDir;
    static std::stack<std::function<void()>> deletors;
    
    //static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    //static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    //static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    //static std::vector<const char*> getRequiredExtensions();
    //static bool checkValidationLayerSupport();
};