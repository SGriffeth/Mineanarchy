#pragma once
#include <vector>
#include <ma_UtilityFunctions.h>
#include <ma_VisibleChunkGrid.h>
#include <ma_Mesher.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <ma_Vertex.h>
#include <ma_VoxelVertex.h>
#include <ma_OzzModel.h>
#include <ma_IndexBufferManager.h>

namespace Mineanarchy {
    class SwapChain;
    class CommandPool;
    class CommandBuffer;
    class RenderPass;
    class LogicalDevice;
    class GraphicsPipeline;
    class DescriptorSet;
    class DescriptorSetLayout;
    class UniformBuffer;
    class Camera;
    class Buffer;
}

namespace Mineanarchy {
    class Instance {

        public:
        Instance() = default;

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };
        
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        #ifdef NDEBUG
        const bool enableValidationLayers = false;
        #else
        const bool enableValidationLayers = true;
        #endif

        void run();
        void LoadModels(int condition);
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
        void createInstance();
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };
        struct mvpMat {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        };
        QueueFamilyIndices findQueueFamilies();
        Instance::SwapChainSupportDetails querySwapChainSupport();
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        void createSurface();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();

        void createLogicalDevice(VkDevice* dev, VkDeviceCreateInfo* createInfo);

        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createMvpUbo();

        private:
        const unsigned int chunkSize = 16;
        const unsigned int SEA_LEVEL = 30;
        const unsigned int gridHalfSideLength = 10;
        unsigned int currentFrame = 0;
        const int MAX_FRAMES_IN_FLIGHT = 2;
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        GLFWwindow* window;
        void* mvpData;

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        //VkQueue graphicsQueue;
        //VkQueue presentQueue;

        int loadModels = 1;
        unsigned int previousCameraX, previousCameraY, previousCameraZ;
        TerrainGenerator* terrainGenerator;
        VisibleChunkGrid* visibleChunkGrid;
        Mesher* mesher;

        SwapChain* swapChain;
        LogicalDevice* logDevice;
        GraphicsPipeline* graphicsPipeline;
        RenderPass* renderPass;
        CommandBuffer* commandBuffers;
        CommandPool* commandPool;
        std::vector<UniformBuffer*> uniformBuffers;
        ma_OzzModel model;
        std::vector<glm::mat4> boneTransforms;
        /*ma_VkBuffer* vertexBuffer;
        ma_VkBuffer* indexBuffer;*/
        Camera* camera;
        std::vector<DescriptorSetLayout*> descriptorSetLayouts;
        std::vector<DescriptorSet*> descriptorSets;

        //std::vector<ma_Vertex> animVertices;
        std::vector<unsigned int> animIndices;
        std::vector<VoxelVertex> vertices;
        std::vector<unsigned int> indices;
        IndexBufferManager* iboManager;
        IndexBufferManager* vboManager;
        VkDevice device;
        VkRenderPass vkRenderPass;
        std::vector<VkCommandBuffer> vkCommandBuffers;
        VkCommandPool vkCommandPool;
        VkSwapchainKHR vkSwapChain;
        Buffer* vertexBuffer;
        Buffer* indexBuffer;
        std::vector<VkDescriptorSetLayout> vkDescriptorSetLayouts;
        std::vector<VkDescriptorSet> vkDescriptorSets;

        VkExtent2D swapChainExtent;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkQueue presentQueue;
        VkQueue graphicsQueue;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        Instance& operator=(const Instance&) = delete;
        Instance(const Instance&) = delete;

        void drawFrame();
        void createUniformBuffers();
        void createDescriptorSetLayouts();
        void createDescriptorSets();
        void createSyncObjects();
        void createCamera();
        void createVertexBuffers();
        void createIndexBuffers();
        void createModels();
        void createMesher();

        void updateUniformBuffers();

        friend class SwapChain;
    };
}