cmake_minimum_required(VERSION 3.11)

project(vulkantutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/23_descriptor_sets.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}  PRIVATE ${Vulkan_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)