cmake_minimum_required(VERSION 3.11)

project(shadermoduleschapter VERSION 1.0)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}  PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE assimpskeletalanimation)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)