
#include <fbxsdk.h>
#include <ozz/animation/animation.h>
#include <vector>

// Function to recursively extract joints from FBX
void ExtractJointsRecursive(FbxNode* node, std::vector<ozz::animation::Joint>& joints, int parentIndex) {
    if (!node) return;

    // Create a joint based on the FBX node
    ozz::animation::Joint joint;
    joint.name = node->GetName();
    joint.parentIndex = parentIndex;

    // Get the bind pose matrix (initial transformation)
    FbxAMatrix bindPoseMatrix = node->EvaluateGlobalTransform(); // or EvaluateLocalTransform() if you prefer

    // Convert FBX matrix to OZZ matrix format
    ozz::math::Float4x4 bindPose;
    for (int i = 0; i < 16; ++i) {
        bindPose[i] = static_cast<float>(bindPoseMatrix[i]);
    }
    joint.bindPose = bindPose; // Assign to joint's bindPose or similar property

    // Add joint to the list
    joints.push_back(joint);

    // Recursively process children
    for (int i = 0; i < node->GetChildCount(); ++i) {
        ExtractJointsRecursive(node->GetChild(i), joints, joints.size() - 1);
    }
}

// Main function to extract joints
std::vector<ozz::animation::Joint> ExtractJointsFromFBX(FbxScene* scene) {
    std::vector<ozz::animation::Joint> joints;

    if (!scene) return joints;

    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode) {
        ExtractJointsRecursive(rootNode, joints, -1); // Root has no parent
    }

    return joints;
}

// Function to extract keyframes from a node
void ExtractKeyframesForNode(FbxNode* node, FbxAnimLayer* animLayer, std::vector<ozz::animation::Keyframe>& keyframes) {
    if (!node || !animLayer) return;

    FbxAnimCurve* animCurve = node->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X);
    if (animCurve) {
        // Extract keyframes from X component
        for (int i = 0; i < animCurve->KeyGetCount(); ++i) {
            FbxTime time = animCurve->KeyGetTime(i);
            FbxDouble value = animCurve->KeyGetValue(i);
            keyframes.push_back({time.GetMilliSeconds(), value});
        }
    }

    // Repeat for Y and Z components, and for rotation/scale if needed
}

// Main function to extract all keyframes
std::vector<ozz::animation::Keyframe> ExtractKeyframesFromFBX(FbxScene* scene) {
    std::vector<ozz::animation::Keyframe> keyframes;

    if (!scene) return keyframes;

    FbxAnimStack* animStack = scene->GetSrcObject<FbxAnimStack>(0);
    FbxAnimLayer* animLayer = animStack ? animStack->GetMember<FbxAnimLayer>(0) : nullptr;

    if (animLayer) {
        FbxNode* rootNode = scene->GetRootNode();
        if (rootNode) {
            for (int i = 0; i < rootNode->GetChildCount(); ++i) {
                ExtractKeyframesForNode(rootNode->GetChild(i), animLayer, keyframes);
            }
        }
    }

    return keyframes;
}

void LoadAnimation2() {
    FbxManager* fbxManager = FbxManager::Create();
    FbxImporter* importer = FbxImporter::Create(fbxManager, "");
    FbxScene* scene = FbxScene::Create(fbxManager, "myScene");

    if (!importer->Initialize("path_to_your_file.fbx", -1, fbxManager->GetIOSettings())) {
        std::cerr << "FBX Importer initialization failed: " << importer->GetStatus().GetErrorString() << std::endl;
        return 1;
    }

    importer->Import(scene);
    importer->Destroy();

    struct AnimationData {
        std::vector<ozz::animation::Joint> joints;
        std::vector<ozz::animation::Keyframe> keyframes;
    };

    AnimationData animation_data;

    animation_data.joints = ExtractJointsFromFBX(scene);
    animation_data.keyframes = ExtractKeyframesFromFBX(scene);

    ozz::animation::offline::AnimationBuilder animationBuilder;
    ozz::animation::Animation* animation = animationBuilder.Build(animation_data);

    if (!animation) {
        std::cerr << "Failed to build OZZ animation" << std::endl;
        return 1;
    }

}
