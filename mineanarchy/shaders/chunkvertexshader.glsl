#version 450

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform PushConstantData {
    uint useBoneTransformations; // Use an unsigned integer for the boolean
} pushConstants;

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 0) uniform BoneTransforms {
    mat4 boneTransforms[300];
} bones;

/*vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)

    
);*/

vec3 positions[3] = vec3[] (
    vec3(0, 0.5, 0),
    vec3(-0.5, 0, 0),
    vec3(0.5, 0, 0)
);

const vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    //gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1);
    //gl_Position = ubo.proj * ubo.view * vec4(positions[gl_VertexIndex], 1.0);
    if(pushConstants.useBoneTransformations == 0) {
        gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1.0);
    } else {
        gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1.0);
    }
    //gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1.0);
    fragColor = colors[gl_VertexIndex % 3];
}