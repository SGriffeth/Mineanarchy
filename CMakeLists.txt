cmake_minimum_required(VERSION 3.11)

project(vulkantutorial VERSION 1.0)

include(ExternalProject)

ExternalProject_Add(
    ozz-animation
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation"
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build"
    GIT_REPOSITORY https://github.com/guillaumeblanc/ozz-animation.git
    GIT_TAG master

    UPDATE_COMMAND ""  # Prevent any updates
    CONFIGURE_COMMAND ""  # Skip the configure step
    BUILD_COMMAND ""  # Skip the build step
    INSTALL_COMMAND ""  # Skip the install step
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

option(ozz_build_samples "Build the samples" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SkeletalAnimation)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation/samples)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation/samples/framework)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/ma_Instance.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_UtilityFunctions.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_LogicalDevice.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_SwapChain.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_GraphicsPipeline.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_RenderPass.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_CommandBuffer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_CommandPool.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_DescriptorSet.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_DescriptorSetLayout.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_UniformBuffer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_Camera.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_Vertex.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_VkBuffer2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ma_OzzModel.cpp)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ozz-animation-build/samples/framework)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}  PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Link OZZ-Animation libraries to your executable
target_link_libraries(${PROJECT_NAME} PRIVATE sample_framework)
target_link_libraries(${PROJECT_NAME} PRIVATE ozz_animation_offline)
target_link_libraries(${PROJECT_NAME} PRIVATE ozz_animation)
target_link_libraries(${PROJECT_NAME} PRIVATE ozz_base)
target_link_libraries(${PROJECT_NAME} PRIVATE ozz_geometry)
target_link_libraries(${PROJECT_NAME} PRIVATE ozz_options)