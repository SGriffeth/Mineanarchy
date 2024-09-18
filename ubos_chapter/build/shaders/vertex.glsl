#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

/*vec3 positions[3] = vec3[](
    vec3(-0.5f, -0.5f, 0.0f),
    vec3(0.5f, -0.5f, 0.0f),
    vec3(0.0f,  0.5f, 0.0f)

    
);*/

/*vec3 positions[3] = vec3[] (
    vec3(-0.452665, -0.603553, 0.400901),
    vec3(0.452665, -0.603553, 0.400901),
    vec3(0, 0.603553, 0.400901)
);*/

/*vec3 positions[3] = vec3[] (
    vec3(-0.5, -0.5, 0.2),
    vec3(0, 0.5, 0.2),
    vec3(0.5, -0.5, 0.2)
);*/

vec3 positions[3] = vec3[] (
    vec3(0.0, -0.5, 0),
    vec3(0.5, 0.5, 0),
    vec3(-0.5, 0.5, 0)
);

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    //gl_Position = ubo.proj * ubo.view * vec4(positions[gl_VertexIndex], 1.0);
    gl_Position = vec4(positions[gl_VertexIndex], 1.0);
    gl_Position.x /=2;
    gl_Position.y /=2;
    gl_Position.z /=2;
    //gl_Position = vec4(positions[gl_VertexIndex], 0, 1.0);
}