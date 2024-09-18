#pragma once
#include <vulkan/vulkan.h>
#include <array>
#include <glm/vec2.hpp> // Include the header for vec2
#include <glm/vec3.hpp> // Include the header for vec3
#include <vector>
const size_t NUM_OF_BONES_PER_VERTEX = 4; 

struct ma_Vertex {
    glm::vec3 pos;
    unsigned int boneIndices[NUM_OF_BONES_PER_VERTEX];
    float boneWeights[NUM_OF_BONES_PER_VERTEX];
    ma_Vertex() {
        pos.x = 0;
        pos.y = 0;
        pos.z = 0;
    }

    ma_Vertex(const glm::vec3& p) {
        pos.x = p.x;
        pos.y = p.y;
        pos.z = p.z;
    }

    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

};