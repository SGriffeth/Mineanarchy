#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ma_Camera.h>
#include <cstring>
#include <iostream>
#include <cmath>

glm::vec3 Mineanarchy::Camera::cameraFront = glm::vec3(0, 0, 0);
glm::vec3 Mineanarchy::Camera::cameraPosition = glm::vec3(0, 0, 1);
glm::vec3 Mineanarchy::Camera::cameraUp = glm::vec3(0, -1, 0);

void Mineanarchy::Camera::updateModelMat(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle) {
    _mvpMat.model = glm::mat4(1.0f);
    _mvpMat.model = glm::translate(_mvpMat.model, translation); // Translate
    _mvpMat.model = glm::rotate(_mvpMat.model, glm::radians(rotationAngle), rotationAxis); // Rotate
    _mvpMat.model = glm::scale(_mvpMat.model, glm::vec3(scale)); // Scale
}

void Mineanarchy::Camera::updateViewMat(glm::vec3 up) {
    cameraUp = up;
    _mvpMat.view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Mineanarchy::Camera::updateProjectionMat(float fov, float aspectRatio, float nearPlane, float farPlane) {
    _mvpMat.proj = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
//    _mvpMat.proj[1][1] *= -1;
    // Print the matrix
    
}

void Mineanarchy::Camera::printTransformations() {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << _mvpMat.proj[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Vertex1:" << std::endl;
    glm::vec4 vertex = _mvpMat.proj * _mvpMat.view * glm::vec4(0, 0.5, 0, 1);
    
    for(int i = 0; i < 4; i++) {
        std::cout << vertex[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vertex2:" << std::endl;
    glm::vec4 vertex2 = _mvpMat.proj * _mvpMat.view * glm::vec4(-0.5, 0, 0, 1);

    for(int i = 0; i < 4; i++) {
        std::cout << vertex2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vertex3:" << std::endl;
    glm::vec4 vertex3 = _mvpMat.proj * _mvpMat.view * glm::vec4(0.5, 0, 0, 1);

    for(int i = 0; i < 4; i++) {
    std::cout << vertex3[i] << " ";
    }
    std::cout << std::endl;
}

void Mineanarchy::Camera::copyMvpTo(void* buffer) {
    memcpy(buffer, &_mvpMat, sizeof(mvpMat));
}

void Mineanarchy::Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = 0;
    static float lastY = 0;
    static float pitch = 0;
    static float yaw = 0;
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // adjust accordingly
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw -= xoffset;
    pitch += yoffset;

    // Constrain pitch (optional)
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    /*if(yaw > 359.0f) {
        yaw = 359.0f;
    }
    if(yaw < 0.0f) {
        yaw = 0.0f;
    }*/

    // Normalize yaw angle to avoid precision issues
    if (yaw > 180.0f)
        yaw -= 360.0f;
    else if (yaw < -180.0f)
        yaw += 360.0f;
    //std::cout << "pitch: " << pitch << ", yaw: " << yaw << std::endl;

    // Update front vector
    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// GLFW callback function for keyboard input
void Mineanarchy::Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float cameraSpeed = 2.5f;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}