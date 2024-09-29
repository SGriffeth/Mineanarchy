#pragma once
#include <ma_Vertex.h>
#include <vector>
#include <SkeletalAnimation/SkeletalModel.h>
#include <string.h>
#include <ma_Instance.h>

namespace Mineanarchy {
    class Model {
        private:
        std::vector<ma_Vertex>* vertices;
        std::vector<uint16_t>* indices;
        SA::SkeletalModel saModel;
        std::string fileName;
        public:
        Model(const std::string& file, std::vector<ma_Vertex>* vertices, std::vector<uint16_t>* indices);
        void update(float time);
        void createModel();
        void createModel(unsigned int i);
        //void createModel(const std::vector<ma_Vertex>& vertices, const std::vector<uint16_t>& indices);

        //friend void Instance::initVulkan();
    };
}