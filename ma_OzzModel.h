//#include <ozz-animation/include/ozz/animation/animation.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/skeleton_utils.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/animation_utils.h>

#include <ozz/animation/offline/animation_builder.h>
#include <ozz/animation/offline/skeleton_builder.h>
#include <ozz/animation/offline/raw_skeleton.h>
#include <ozz/animation/offline/raw_animation.h>
#include <ozz/base/maths/soa_transform.h>

//#include <iostream>
//#include <fstream>
#include <ozz/base/io/archive.h>
#include <ozz/base/io/stream.h>

#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/base/maths/transform.h>

#include <samples/framework/utils.h>
#include <glm/mat4x4.hpp>

#include <ma_Vertex.h>

class ma_OzzModel {
    public:
    void UpdateBoneTransforms(std::vector<glm::mat4>& matrices, float time);
    void LoadAnimation(const std::string& animation_file, const std::string& skeleton_file, const std::string& mesh_file, std::vector<ma_Vertex>& vertices, std::vector<uint16_t>& indices);
    private:
    ozz::animation::Animation animation;
    ozz::animation::Skeleton skeleton;
    ozz::sample::PlaybackController controller_;
    ozz::animation::SamplingJob::Context context_;
    std::vector<glm::mat4> ConvertAllSoATransformsToMatrices(const std::vector<ozz::math::SoaTransform>& soa_transforms);
};