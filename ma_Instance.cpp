#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>
#include <chrono>


#include <ma_Instance.h>
#include <ma_LogicalDevice.h>
#include <ma_RenderPass.h>
#include <ma_CommandBuffer.h>
#include <ma_CommandPool.h>
#include <ma_GraphicsPipeline.h>
#include <ma_UtilityFunctions.h>
#include <ma_SwapChain.h>
#include <ma_DescriptorSetLayout.h>
#include <ma_Camera.h>
#include <ma_Vertex.h>
#include <ma_VkBuffer2.h>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>    // For std::stringstream

    void Mineanarchy::Instance::run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }



    

    void Mineanarchy::Instance::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        // Set the callback function for mouse movement
        glfwSetCursorPosCallback(window, Camera::mouse_callback);
        glfwSetKeyCallback(window, Camera::key_callback);

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Mineanarchy::Instance::initVulkan() {
        createCamera();
        createMesher();
        mesher = new Mesher(vertices, indices, 1, *visibleChunkGrid, *terrainGenerator, *vboManager, *iboManager);
        auto meshStart = std::chrono::high_resolution_clock::now();
        mesher->Mesh();
        //mesher->AwaitChunkMeshing();
        auto meshEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd - meshStart).count();
        std::cout << "Done w first meshing, took: " << totalDuration << std::endl;

        createInstance();
        setupDebugMessenger();
        createSurface();
        Instance::pickPhysicalDevice();
        logDevice = new LogicalDevice(this);
        logDevice->createLogicalDevice(physicalDevice, &presentQueue, &graphicsQueue);
        device = logDevice->device;
        swapChain = new SwapChain(logDevice->device);
        swapChain->createSwapChain(*this);
        

        swapChain->createImageViews();

        renderPass = new RenderPass();
        renderPass->createRenderPass(logDevice->device, swapChain->getImageFormat());
        std::string gameD;
        UtilityFunctions::getGameDirectory(gameD);
        graphicsPipeline = new GraphicsPipeline(logDevice->device);
        std::cout << gameD + std::string("/shaders/vert.spv").data() << std::endl;
        vkRenderPass = renderPass->renderPass;
        createDescriptorSetLayouts();
        vkDescriptorSetLayouts.resize(descriptorSetLayouts.size());
        for(uint i = 0; i < descriptorSetLayouts.size(); i++) {
            vkDescriptorSetLayouts[i] = descriptorSetLayouts[i]->descriptorSetLayout;
        }
        graphicsPipeline->createGraphicsPipeline((gameD + std::string("/shaders/vert.spv")).data(), (gameD + "/shaders/frag.spv").data(), vkDescriptorSetLayouts, vkRenderPass);
        swapChain->createFramebuffers(vkRenderPass);
        swapChainExtent = swapChain->swapChainExtent;
        swapChainFramebuffers = swapChain->swapChainFramebuffers;
        vkSwapChain = swapChain->swapChain;
        commandPool = new CommandPool(device);
        commandPool->createCommandPool(*this);
        vkCommandPool = commandPool->pool;
        if(loadModels)
        createModels();
    createDescriptorSets();
    vkDescriptorSets.resize(descriptorSets.size());
        for(uint i = 0; i < descriptorSets.size(); i++) {
            vkDescriptorSets[i] = descriptorSets[i]->descriptorSet;
        }
        createUniformBuffers();
        camera->updateProjectionMat(45.0f, swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 450.0f);
        camera->updateModelMat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), 0);
        camera->updateViewMat(glm::vec3(0, -1, 0));
        camera->printTransformations();
        mvpData = new char[sizeof(Camera::mvpMat)];
        camera->copyMvpTo(mvpData);
        updateUniformBuffers();
        createVertexBuffers();
        createIndexBuffers();
        size_t voxelGridSideLength = visibleChunkGrid->getGridHalfSideLength()*2*visibleChunkGrid->getChunkSize();
        commandBuffers = new CommandBuffer[MAX_FRAMES_IN_FLIGHT];
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            commandBuffers[i] = CommandBuffer(commandPool);
            commandBuffers[i].createCommandBuffer();
        }

        vkCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkCommandBuffers[i] = commandBuffers[i].commandBuffer;
        }
        createSyncObjects();

        /*UtilityFunctions::addDeletor([&]() {
            vkDestroyBuffer(device, vkVertexBuffer, nullptr);
            vkFreeMemory(device, vertexBuffer->bufferMemory, nullptr);
            vkDestroyBuffer(device, vkIndexBuffer, nullptr);
            vkFreeMemory(device, indexBuffer->bufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::createMesher() {
        iboManager = new IndexBufferManager(350*sizeof(unsigned int));
        vboManager = new IndexBufferManager(350*sizeof(vertices[0]));
        terrainGenerator = new TerrainGenerator(SEA_LEVEL);
        visibleChunkGrid = new VisibleChunkGrid(*terrainGenerator, chunkSize, gridHalfSideLength);
        terrainGenerator->SetChunkGrid(visibleChunkGrid);

        visibleChunkGrid->UpdateGridPosition(camera->getPosition().x/chunkSize, camera->getPosition().y/chunkSize, camera->getPosition().z/chunkSize);
    }

    void Mineanarchy::Instance::createModels() {
        //model = ma_OzzModel();
        /*UtilityFunctions::addDeletor([this]{
            delete this->model;
        });*/
        std::string gameDir;
        UtilityFunctions::getGameDirectory(gameDir);
        model.LoadAnimation(gameDir + std::string("/") + UtilityFunctions::getConfigValue("animationFile"), gameDir + std::string("/") + UtilityFunctions::getConfigValue("skeletonFile"), gameDir + std::string("/") + UtilityFunctions::getConfigValue("meshFile"), animVertices, animIndices);
        model.UpdateBoneTransforms(boneTransforms, 0);
        if(boneTransforms.size() > 300) {
            std::stringstream ss;
            ss << "Error: boneTransforms size is " << boneTransforms.size()
               << ", which is more than the max size.";
            throw std::runtime_error(ss.str());
        }
        bool first0 = true;
        for(uint i = 0; i < animVertices.size(); i++) {
            if(vertices[i].pos[0] == 0 && vertices[i].pos[1] == 0 && vertices[i].pos[2] == 0 && !first0) {
                continue;
            }
            if(vertices[i].pos[0] == 0 && vertices[i].pos[1] == 0 && vertices[i].pos[2] == 0) first0 = false;

            std::cout << "vertices(" << i << ") = " << "(" << vertices[i].pos[0] << "," << vertices[i].pos[1] << "," << vertices[i].pos[2] << ")" << std::endl;
        }

        for(uint i = 0; i < animIndices.size(); i++) {
            std::cout << "indices(" << i << ") = " << indices[i] << std::endl;
        }
    }

    void Mineanarchy::Instance::createVertexBuffers() {
        //size_t estimatedSize = chunkSize*visibleChunkGrid->getGridHalfSideLength()*2 * chunkSize*visibleChunkGrid->getGridHalfSideLength()*2 * chunkSize*visibleChunkGrid->getGridHalfSideLength()*2;
        vertices.reserve(vboManager->GetRecBufferCapacity());
        vertexBuffer = new Buffer(device, sizeof(vertices[0]) * vboManager->GetRecBufferCapacity());
        vertexBuffer->createBuffer(graphicsQueue, vkCommandPool, physicalDevice, vertices.data(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        //vertexBuffer->updateBuffer(vertices);
        /*UtilityFunctions::addDeletor([this]() {
            vkDestroyBuffer(device, vkVertexBuffer, nullptr);
            vkFreeMemory(device, vertexBufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::createIndexBuffers() {
        //size_t estimatedSize = chunkSize*visibleChunkGrid->getGridHalfSideLength()*2 * chunkSize*visibleChunkGrid->getGridHalfSideLength()*2 * chunkSize*visibleChunkGrid->getGridHalfSideLength()*2 * 6*6;
        //estimatedSize /= 2; // tentatively say that we need half that
        //indices = new unsigned int[estimatedSize];
        //unsigned int* testBuffer = new unsigned int[estimatedSize];
        //indices.reserve(estimatedSize);
        indices.reserve(iboManager->GetRecBufferCapacity());
        indexBuffer = new Buffer(device, sizeof(unsigned int) * iboManager->GetRecBufferCapacity());
        indexBuffer->createBuffer(graphicsQueue, vkCommandPool, physicalDevice, indices.data(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        //indexBuffer->updateBuffer(indices);
         /*UtilityFunctions::addDeletor([this]() {
            vkDestroyBuffer(device, indexBuffer, nullptr);
            vkFreeMemory(device, indexBufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            auto start = std::chrono::high_resolution_clock::now();
            glfwPollEvents();
            camera->updateViewMat(glm::vec3(0, -1, 0));
            //camera->printTransformations();
            mvpData = new char[sizeof(Camera::mvpMat)];
            camera->copyMvpTo(mvpData);
            
            auto frameDrawStart = std::chrono::high_resolution_clock::now();
            drawFrame();
            auto frameDrawEnd = std::chrono::high_resolution_clock::now();
            if(!((unsigned int)camera->getPosition().x/visibleChunkGrid->getChunkSize() == previousCameraX &&
            (unsigned int)camera->getPosition().y/visibleChunkGrid->getChunkSize() == previousCameraY &&
            (unsigned int)camera->getPosition().z/visibleChunkGrid->getChunkSize() == previousCameraZ)) {
                std::cout << "loading again pos: (" << camera->getPosition().x << ", " << camera->getPosition().y << ", " << camera->getPosition().z << ")" << std::endl;
                auto gridUpdateStart = std::chrono::high_resolution_clock::now();
                visibleChunkGrid->UpdateGridPosition(camera->getPosition().x/visibleChunkGrid->getChunkSize(), camera->getPosition().y/visibleChunkGrid->getChunkSize(), camera->getPosition().z/visibleChunkGrid->getChunkSize());
                auto gridUpdateEnd = std::chrono::high_resolution_clock::now();

                unsigned int previousSize = iboManager->GetRecBufferCapacity();
                unsigned int vboPreviousSize = vboManager->GetRecBufferCapacity();
                auto meshStart = std::chrono::high_resolution_clock::now();
                mesher->Mesh();
                //mesher->AwaitChunkMeshing();
                auto meshEnd = std::chrono::high_resolution_clock::now();
                auto bufferResizeStart = std::chrono::high_resolution_clock::now();
                if(previousSize != iboManager->GetRecBufferCapacity())
                indexBuffer->resizeBuffer(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, iboManager->GetRecBufferCapacity()*sizeof(unsigned int));
            
                if(vboPreviousSize != vboManager->GetRecBufferCapacity())
                vertexBuffer->resizeBuffer(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vboManager->GetRecBufferCapacity()*sizeof(vertices[0]));
                auto bufferResizeEnd = std::chrono::high_resolution_clock::now();
                
                vertexBuffer->updateBuffer(vertices.data());
                indexBuffer->updateBuffer(indices.data());
                previousCameraX = camera->getPosition().x/visibleChunkGrid->getChunkSize();
                previousCameraY = camera->getPosition().y/visibleChunkGrid->getChunkSize();
                previousCameraZ = camera->getPosition().z/visibleChunkGrid->getChunkSize();
                auto end = std::chrono::high_resolution_clock::now();

                // Calculate durations
                auto bufferResizeDuration = std::chrono::duration_cast<std::chrono::microseconds>(bufferResizeEnd - bufferResizeStart).count();
                auto frameDrawDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameDrawEnd - frameDrawStart).count();
                auto gridUpdateDuration = std::chrono::duration_cast<std::chrono::microseconds>(gridUpdateEnd - gridUpdateStart).count();
                auto meshDuration = std::chrono::duration_cast<std::chrono::microseconds>(meshEnd - meshStart).count();
                auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                std::cout << "Buffer resize time: " << bufferResizeDuration << "µs, Frame draw time: " <<  frameDrawDuration << "µs, Grid update time: " << gridUpdateDuration << "µs, Meshing time: " << meshDuration << "µs, Total time: " << totalDuration << "µs" << std::endl;
            }
        }

        vkDeviceWaitIdle(device);
    }

    void Mineanarchy::Instance::cleanup() {
        //vkDestroySwapchainKHR(device, swapChain, nullptr);
        //Deletion queue
        UtilityFunctions::runDeletors();

        //indexBuffer->destroy();
        //vertexBuffer->destroy();

        logDevice->destroy();

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
        
        delete logDevice;
    }

    void Mineanarchy::Instance::createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void Mineanarchy::Instance::createCamera() {
        //camera = new Camera(chunkSize*100, 81, chunkSize*100); // If the camera is too high up no vertices will be generated and hence an empty vertices vector will cause a segfault
        camera = new Camera(10, SEA_LEVEL, 10); // If the camera is too high up no vertices will be generated and hence an empty vertices vector will cause a segfault
        
        //updateUniformBuffers();
    }

    Mineanarchy::Instance::SwapChainSupportDetails Mineanarchy::Instance::querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    Mineanarchy::Instance::SwapChainSupportDetails Mineanarchy::Instance::querySwapChainSupport() {
        return querySwapChainSupport(this->physicalDevice);
    }

    bool Mineanarchy::Instance::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    Mineanarchy::Instance::QueueFamilyIndices Mineanarchy::Instance::findQueueFamilies() {
        return findQueueFamilies(physicalDevice);
    }

    Mineanarchy::Instance::QueueFamilyIndices Mineanarchy::Instance::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }


    bool Mineanarchy::Instance::isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    void Mineanarchy::Instance::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    std::vector<const char*> Mineanarchy::Instance::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool Mineanarchy::Instance::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    void Mineanarchy::Instance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = UtilityFunctions::debugCallback;
    }

    VkResult Mineanarchy::Instance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Mineanarchy::Instance::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    void Mineanarchy::Instance::setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    void Mineanarchy::Instance::createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void Mineanarchy::Instance::createLogicalDevice(VkDevice* dev, VkDeviceCreateInfo* createInfo) {
        if (vkCreateDevice(physicalDevice, createInfo, nullptr, dev) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }
    }

    void Mineanarchy::Instance::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = vkRenderPass;
        renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChainExtent;

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->graphicsPipeline);

            VkViewport viewport{};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float) swapChainExtent.width;
            viewport.height = (float) swapChainExtent.height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;
            vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

            VkRect2D scissor{};
            scissor.offset = {0, 0};
            scissor.extent = swapChainExtent;
            vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
            updateUniformBuffers();
            vkCmdBindDescriptorSets(commandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            graphicsPipeline->pipelineLayout,
            0,
            1,
            &vkDescriptorSets[currentFrame],
            0,
            nullptr);

            VkBuffer vertexBuffers[] = {vertexBuffer->newBuffer};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

            vkCmdBindIndexBuffer(commandBuffer, indexBuffer->newBuffer, 0, VK_INDEX_TYPE_UINT32);

            GraphicsPipeline::PushConstantData pushConstantData;
            pushConstantData.useBoneTransformation = loadModels; // Set to 1 or 0 based on your condition

            vkCmdPushConstants(commandBuffer, graphicsPipeline->pipelineLayout, 
                            VK_SHADER_STAGE_VERTEX_BIT, 
                            0, // Offset (should match your push constant definition)
                            sizeof(GraphicsPipeline::PushConstantData), 
                            &pushConstantData);
            const std::vector<Mesher::ChunkInfo>& chunksToRender = mesher->GetChunksToRender();
            for(size_t i = 0; i < chunksToRender.size(); i++) {
                if(chunksToRender[i].iboEndIndex < chunksToRender[i].iboStartIndex) throw std::runtime_error("end index is less than start index");
                vkCmdDrawIndexed(commandBuffer, chunksToRender[i].iboEndIndex - chunksToRender[i].iboStartIndex, 1, chunksToRender[i].iboStartIndex, 0, 0);
            }
            //vkCmdDrawIndexed(commandBuffer, indices.size(), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }

void Mineanarchy::Instance::drawFrame() {
    static auto start = std::chrono::steady_clock::now();
    vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &inFlightFences[currentFrame]);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, vkSwapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    vkResetCommandBuffer(vkCommandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
    // Record the end time
    auto end = std::chrono::steady_clock::now();
    
    // Calculate the elapsed time
    std::chrono::duration<float> elapsed = end - start;
    //std::cout << elapsed.count() << std::endl;
    /*if(!((unsigned int)camera->getPosition().x/visibleChunkGrid->getChunkSize() == previousCameraX &&
            (unsigned int)camera->getPosition().y/visibleChunkGrid->getChunkSize() == previousCameraY &&
            (unsigned int)camera->getPosition().z/visibleChunkGrid->getChunkSize() == previousCameraZ)) {
        vertexBuffer->updateBuffer(vertices);
        indexBuffer->updateBuffer(indices);
    }*/
    recordCommandBuffer(vkCommandBuffers[currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vkCommandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {vkSwapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(presentQueue, &presentInfo);
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    start = std::chrono::steady_clock::now();
}

void Mineanarchy::Instance::createSyncObjects() {
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
        UtilityFunctions::addDeletor([=]() {
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr); // problem here
            vkDestroyFence(device, inFlightFences[i], nullptr);
        });
    }
    
    /*VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }

    UtilityFunctions::addDeletor([&]() {
        vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
        vkDestroyFence(device, inFlightFence, nullptr);
    });*/
}

void Mineanarchy::Instance::createUniformBuffers() {
    uniformBuffers.reserve(MAX_FRAMES_IN_FLIGHT);

    for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        uniformBuffers.push_back(new UniformBuffer(*descriptorSets[i+0], sizeof(mvpMat)));
        uniformBuffers[i]->createUniformBuffer(physicalDevice);        
    }

    /*for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if(boneTransforms.size() == 0) {
            uniformBuffers.push_back(new UniformBuffer(*descriptorSets[1], 1));
        } else {
            //uniformBuffers.push_back(new UniformBuffer(*descriptorSets[1], boneTransforms.size()));    
            uniformBuffers.push_back(new UniformBuffer(*descriptorSets[1], sizeof(glm::mat4)*boneTransforms.size()));    
        }
        
        uniformBuffers[i+MAX_FRAMES_IN_FLIGHT]->createUniformBuffer(physicalDevice);
    }*/
}

void Mineanarchy::Instance::updateUniformBuffers() {
    //for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VkWriteDescriptorSet descriptorWrite = {};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = vkDescriptorSets[currentFrame]; // Descriptor set to update
        descriptorWrite.dstBinding = 0; // Binding number in the descriptor set layout
        descriptorWrite.dstArrayElement = 0; // Starting element in the array (if an array)
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // Type of descriptor
        descriptorWrite.descriptorCount = 1; // Number of descriptors to update
        descriptorWrite.pBufferInfo = nullptr; // Buffer information to update with
        uniformBuffers[currentFrame]->updateUniformBuffer(mvpData, descriptorWrite);
    //}
    /*if(loadModels)
    for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VkWriteDescriptorSet descriptorWrite2 = {};
        descriptorWrite2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite2.dstSet = vkDescriptorSets[i+MAX_FRAMES_IN_FLIGHT]; // Descriptor set to update
        descriptorWrite2.dstBinding = 0; // Binding number in the descriptor set layout
        descriptorWrite2.dstArrayElement = 0; // Starting element in the array (if an array)
        descriptorWrite2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // Type of descriptor
        descriptorWrite2.descriptorCount = 1; // Number of descriptors to update
        descriptorWrite2.pBufferInfo = nullptr; // Buffer information to update with
        uniformBuffers[i+MAX_FRAMES_IN_FLIGHT]->updateUniformBuffer(boneTransforms.data(), descriptorWrite2);
    }*/
}

void Mineanarchy::Instance::createDescriptorSetLayouts() {
    // Define descriptor set layout binding
    VkDescriptorSetLayoutBinding binding = {};
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding.descriptorCount = 1;
    binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    binding.pImmutableSamplers = nullptr;
    
    // Create descriptor set layout
    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &binding;

    descriptorSetLayouts.reserve(1);

    descriptorSetLayouts.push_back(new DescriptorSetLayout(device, binding, layoutInfo));
    descriptorSetLayouts[0]->createDescriptorSetLayout();
}

void Mineanarchy::Instance::createDescriptorSets() {
    descriptorSets.reserve(MAX_FRAMES_IN_FLIGHT);

    for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        descriptorSets.push_back(new DescriptorSet(descriptorSetLayouts[0]));
        descriptorSets[i+0]->createDescriptorSet();
    }
    
    /*if(loadModels)
    for(unsigned int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        descriptorSets.push_back(new DescriptorSet(descriptorSetLayouts[1]));
        descriptorSets[i+MAX_FRAMES_IN_FLIGHT]->createDescriptorSet();
    }*/
}

uint32_t Mineanarchy::Instance::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Mineanarchy::Instance::LoadModels(int condition) {
    loadModels = condition;
}

int main(int argc, char** argv) {
    int configState = Mineanarchy::UtilityFunctions::queryConfigState();
    if(configState == Mineanarchy::UtilityFunctions::CONFIG_INEXISTENT || configState == Mineanarchy::UtilityFunctions::CONFIG_INVALIDLY_FORMATTED) {
        if(argc < 5) {
            throw std::runtime_error("You must specify a path for the game directory, mesh file, skeleton file, and animation file");
        } else {
            Mineanarchy::UtilityFunctions::createConfig();
            Mineanarchy::UtilityFunctions::setGameDirectory(argv[1]);
            Mineanarchy::UtilityFunctions::setMeshFile(argv[2]);
            Mineanarchy::UtilityFunctions::setSkeletonFile(argv[3]);
            Mineanarchy::UtilityFunctions::setAnimationFile(argv[4]);
            Mineanarchy::UtilityFunctions::writeToConfig();
        }
    } else if(argc > 1) {
        if(strcmp(argv[1], "modelsoff") != 0) {
            switch(argc) {
                case 2:
                    Mineanarchy::UtilityFunctions::createConfig();
                    Mineanarchy::UtilityFunctions::setGameDirectory(argv[1]);
                    Mineanarchy::UtilityFunctions::writeToConfig();
                    break;
                case 3:
                    Mineanarchy::UtilityFunctions::createConfig();
                    Mineanarchy::UtilityFunctions::setGameDirectory(argv[1]);
                    Mineanarchy::UtilityFunctions::setMeshFile(argv[2]);
                    Mineanarchy::UtilityFunctions::writeToConfig();
                    break;
                case 4:
                    Mineanarchy::UtilityFunctions::createConfig();
                    Mineanarchy::UtilityFunctions::setGameDirectory(argv[1]);
                    Mineanarchy::UtilityFunctions::setMeshFile(argv[2]);
                    Mineanarchy::UtilityFunctions::setSkeletonFile(argv[3]);
                    Mineanarchy::UtilityFunctions::writeToConfig();
                    break;
                case 5:
                    Mineanarchy::UtilityFunctions::createConfig();
                    Mineanarchy::UtilityFunctions::setGameDirectory(argv[1]);
                    Mineanarchy::UtilityFunctions::setMeshFile(argv[2]);
                    Mineanarchy::UtilityFunctions::setSkeletonFile(argv[3]);
                    Mineanarchy::UtilityFunctions::setAnimationFile(argv[4]);
                    Mineanarchy::UtilityFunctions::writeToConfig();
                    break;
            }
        }
    }
    
    Mineanarchy::UtilityFunctions::getConfig();

    Mineanarchy::Instance app;
    if(argc > 1)
    if(strcmp(argv[1], "modelsoff") == 0) app.LoadModels(0);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}