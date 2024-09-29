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
        createInstance();
        setupDebugMessenger();
        createSurface();
        Instance::pickPhysicalDevice();
        logDevice = new LogicalDevice(this);
        logDevice->createLogicalDevice(&presentQueue, &graphicsQueue);
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
        createModels();
        createVertexBuffers();
        createIndexBuffers();
        createDescriptorSets();
        createUniformBuffers();
        commandBuffer = new CommandBuffer(commandPool);
        commandBuffer->createCommandBuffer();
        vkCommandBuffer = commandBuffer->commandBuffer;
        createSyncObjects();

        vkDescriptorSets.resize(descriptorSets.size());
        for(uint i = 0; i < descriptorSets.size(); i++) {
            vkDescriptorSets[i] = descriptorSets[i]->descriptorSet;
        }
        createCamera();
        /*UtilityFunctions::addDeletor([&]() {
            vkDestroyBuffer(device, vkVertexBuffer, nullptr);
            vkFreeMemory(device, vertexBuffer->bufferMemory, nullptr);
            vkDestroyBuffer(device, vkIndexBuffer, nullptr);
            vkFreeMemory(device, indexBuffer->bufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::createModels() {
        //model = ma_OzzModel();
        /*UtilityFunctions::addDeletor([this]{
            delete this->model;
        });*/
        std::string gameDir;
        UtilityFunctions::getGameDirectory(gameDir);
        model.LoadAnimation(gameDir + std::string("/") + UtilityFunctions::getConfigValue("animationFile"), gameDir + std::string("/") + UtilityFunctions::getConfigValue("skeletonFile"), gameDir + std::string("/") + UtilityFunctions::getConfigValue("meshFile"), vertices, indices);
        model.UpdateBoneTransforms(boneTransforms, 0);
        if(boneTransforms.size() > 300) {
            std::stringstream ss;
            ss << "Error: boneTransforms size is " << boneTransforms.size()
               << ", which is more than the max size.";
            throw std::runtime_error(ss.str());
        }
        bool first0 = true;
        for(uint i = 0; i < vertices.size(); i++) {
            if(vertices[i].pos[0] == 0 && vertices[i].pos[1] == 0 && vertices[i].pos[2] == 0 && !first0) {
                continue;
            }
            if(vertices[i].pos[0] == 0 && vertices[i].pos[1] == 0 && vertices[i].pos[2] == 0) first0 = false;

            std::cout << "vertices(" << i << ") = " << "(" << vertices[i].pos[0] << "," << vertices[i].pos[1] << "," << vertices[i].pos[2] << ")" << std::endl;
        }

        for(uint i = 0; i < indices.size(); i++) {
            std::cout << "indices(" << i << ") = " << indices[i] << std::endl;
        }
    }

    void Mineanarchy::Instance::createVertexBuffers() {
        vertexBuffer = new Buffer(device, sizeof(vertices[0]) * vertices.size());
        vertexBuffer->createBuffer(graphicsQueue, vkCommandPool, physicalDevice, vertices.data(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        //vertexBuffer->updateBuffer(vertices);
        /*UtilityFunctions::addDeletor([this]() {
            vkDestroyBuffer(device, vkVertexBuffer, nullptr);
            vkFreeMemory(device, vertexBufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::createIndexBuffers() {
        indexBuffer = new Buffer(device, sizeof(indices[0]) * indices.size());
        indexBuffer->createBuffer(graphicsQueue, vkCommandPool, physicalDevice, indices.data(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        //indexBuffer->updateBuffer(indices);
         /*UtilityFunctions::addDeletor([this]() {
            vkDestroyBuffer(device, indexBuffer, nullptr);
            vkFreeMemory(device, indexBufferMemory, nullptr);
        });*/
    }

    void Mineanarchy::Instance::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            camera->updateViewMat(glm::vec3(0, -1, 0));
            //camera->printTransformations();
            mvpData = new char[sizeof(Camera::mvpMat)];
            camera->copyMvpTo(mvpData);
            drawFrame();
        }

        vkDeviceWaitIdle(device);
    }

    void Mineanarchy::Instance::cleanup() {
        //vkDestroySwapchainKHR(device, swapChain, nullptr);
        //Deletion queue
        UtilityFunctions::runDeletors();

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
        camera = new Camera();
        camera->updateModelMat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), 0);
        camera->updateViewMat(glm::vec3(0, -1, 0));
        camera->updateProjectionMat(45.0f, swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 100.0f);
        camera->printTransformations();
        mvpData = new char[sizeof(Camera::mvpMat)];
        camera->copyMvpTo(mvpData);
        updateUniformBuffers();
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
            &vkDescriptorSets[0],
            0,
            nullptr);

            VkBuffer vertexBuffers[] = {vertexBuffer->buffer};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

            vkCmdBindIndexBuffer(commandBuffer, indexBuffer->buffer, 0, VK_INDEX_TYPE_UINT16);

            vkCmdDrawIndexed(commandBuffer, indices.size(), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }

void Mineanarchy::Instance::drawFrame() {
    static auto start = std::chrono::steady_clock::now();
    vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &inFlightFence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, vkSwapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    vkResetCommandBuffer(vkCommandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
    // Record the end time
    auto end = std::chrono::steady_clock::now();
    
    // Calculate the elapsed time
    std::chrono::duration<float> elapsed = end - start;
    //std::cout << elapsed.count() << std::endl;
    vertexBuffer->updateBuffer(vertices.data());
    indexBuffer->updateBuffer(indices.data());
    recordCommandBuffer(vkCommandBuffer, imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vkCommandBuffer;

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
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
    start = std::chrono::steady_clock::now();
}

void Mineanarchy::Instance::createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
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
    });
}

void Mineanarchy::Instance::createUniformBuffers() {
    uniformBuffers.push_back(new UniformBuffer(*descriptorSets[0], sizeof(mvpMat)));
    uniformBuffers[0]->createUniformBuffer(physicalDevice);

    uniformBuffers.push_back(new UniformBuffer(*descriptorSets[1], boneTransforms.size()));
    uniformBuffers[1]->createUniformBuffer(physicalDevice);
}

void Mineanarchy::Instance::updateUniformBuffers() {
    VkWriteDescriptorSet descriptorWrite = {};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = vkDescriptorSets[0]; // Descriptor set to update
    descriptorWrite.dstBinding = 0; // Binding number in the descriptor set layout
    descriptorWrite.dstArrayElement = 0; // Starting element in the array (if an array)
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // Type of descriptor
    descriptorWrite.descriptorCount = 1; // Number of descriptors to update
    descriptorWrite.pBufferInfo = nullptr; // Buffer information to update with
    uniformBuffers[0]->updateUniformBuffer(mvpData, descriptorWrite);

    VkWriteDescriptorSet descriptorWrite2 = {};
    descriptorWrite2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite2.dstSet = vkDescriptorSets[1]; // Descriptor set to update
    descriptorWrite2.dstBinding = 0; // Binding number in the descriptor set layout
    descriptorWrite2.dstArrayElement = 0; // Starting element in the array (if an array)
    descriptorWrite2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // Type of descriptor
    descriptorWrite2.descriptorCount = 1; // Number of descriptors to update
    descriptorWrite2.pBufferInfo = nullptr; // Buffer information to update with
    uniformBuffers[1]->updateUniformBuffer(boneTransforms.data(), descriptorWrite2);
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

    VkDescriptorSetLayoutBinding binding2 = {};
    binding2.binding = 0;
    binding2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding2.descriptorCount = 1;
    binding2.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    binding2.pImmutableSamplers = nullptr;
    
    // Create descriptor set layout
    VkDescriptorSetLayoutCreateInfo layoutInfo2 = {};
    layoutInfo2.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo2.bindingCount = 1;
    layoutInfo2.pBindings = &binding2;

    descriptorSetLayouts.resize(2);

    descriptorSetLayouts[0] = new DescriptorSetLayout(device, binding, layoutInfo);
    descriptorSetLayouts[0]->createDescriptorSetLayout();

    descriptorSetLayouts[1] = new DescriptorSetLayout(device, binding2, layoutInfo2);
    descriptorSetLayouts[1]->createDescriptorSetLayout();
}

void Mineanarchy::Instance::createDescriptorSets() {
    descriptorSets.resize(2);

    descriptorSets[0] = new DescriptorSet(descriptorSetLayouts[0]);
    descriptorSets[0]->createDescriptorSet();

    descriptorSets[1] = new DescriptorSet(descriptorSetLayouts[1]);
    descriptorSets[1]->createDescriptorSet();
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
    } else {
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
    
    Mineanarchy::UtilityFunctions::getConfig();
    
    Mineanarchy::Instance app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}