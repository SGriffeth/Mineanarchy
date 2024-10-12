#pragma once
#include <vulkan/vulkan.h>
#include <array>
#include <glm/vec3.hpp> // Include the header for vec3

namespace Mineanarchy {
    struct VoxelVertex {
        glm::vec3 pos;

        VoxelVertex() {
            
        }

        VoxelVertex(const glm::vec3& p) {
            pos.x = p.x;
            pos.y = p.y;
            pos.z = p.z;
        }

        static VkVertexInputBindingDescription getBindingDescription();

        static std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions();
    };
}