#pragma once
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>

namespace Mineanarchy {
    class Camera {
        public:
        struct mvpMat {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        };
        void copyMvpTo(void*);
        void updateModelMat(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
        void updateViewMat(glm::vec3 cameraUp);
        void updateProjectionMat(float fov, float aspectRatio, float nearPlane, float farPlane);
        void printTransformations();
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        
        private:
        struct mvpMat _mvpMat;
        static glm::vec3 cameraUp;
        static glm::vec3 cameraFront;
        static glm::vec3 cameraPosition;

    };
}