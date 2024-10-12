#include <ma_UtilityFunctions.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdexcept>

std::stack<std::function<void()>> Mineanarchy::UtilityFunctions::deletors;
const char* Mineanarchy::UtilityFunctions::CONFIG_NAME = "maConf.json";
nlohmann::json Mineanarchy::UtilityFunctions::config;

int Mineanarchy::UtilityFunctions::queryConfigState() {
    std::vector<char> buffer;
    if(!readFile(std::string(CONFIG_NAME), buffer)) { // Determine if the file exists
        return CONFIG_INEXISTENT;
    }
    try {
        nlohmann::json parsedjs = nlohmann::json::parse(buffer.data(), buffer.data() + buffer.size());
    } catch (const std::exception& ex) {
        std::cerr << "Error parsing JSON: " << ex.what() << std::endl;
        return CONFIG_INVALIDLY_FORMATTED;
    }
    return CONFIG_READABLE;
}

void Mineanarchy::UtilityFunctions::getGameDirectory(std::string& gameDir) {
    gameDir = config["gameDir"];
}

std::string Mineanarchy::UtilityFunctions::getConfigValue(const char* name) {
    return config[name];
}

void Mineanarchy::UtilityFunctions::getConfig() {
    std::ifstream configFile(CONFIG_NAME);
    if (!configFile) {
        throw std::runtime_error("unable to open config");
    }

    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(configFile)),
        (std::istreambuf_iterator<char>())
    );
    try {
        config = nlohmann::json::parse(bytes.data(), bytes.data() + bytes.size());
    } catch (const std::exception& ex) {
        throw std::runtime_error("Error parsing JSON: " + std::string(ex.what()));
    }
    configFile.close();
}

void Mineanarchy::UtilityFunctions::createConfig() {
    nlohmann::json myObject = {
        {"gameDir", ""},
        {"meshFile" , ""},
        {"skeletonFile" , ""},
        {"animationFile" , ""}
    };
    std::ofstream configFile(CONFIG_NAME);
    configFile << myObject.dump(); // Write data to the file
    configFile << std::endl;
    configFile.close(); // Close the file
    config = myObject;
}

void Mineanarchy::UtilityFunctions::setGameDirectory(const char* name) {
    std::filesystem::create_directories(name);
    std::filesystem::create_directory(std::string(name) + "/chunks");
    std::filesystem::create_directory(std::string(name) + "/shaders");
    config["gameDir"] = name;
}

void Mineanarchy::UtilityFunctions::setMeshFile(const char* name) {
    config["meshFile"] = name;
} 

void Mineanarchy::UtilityFunctions::setSkeletonFile(const char* name) {
    config["skeletonFile"] = name;  
} 

void Mineanarchy::UtilityFunctions::setAnimationFile(const char* name) {
    config["animationFile"] = name;
} 

void Mineanarchy::UtilityFunctions::writeToConfig() {
    std::ofstream configFile(CONFIG_NAME);
    configFile << config.dump() << std::endl;
    configFile.close();
}

VKAPI_ATTR VkBool32 VKAPI_CALL Mineanarchy::UtilityFunctions::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void Mineanarchy::UtilityFunctions::addDeletor(std::function<void()> deletor) {
    deletors.push(deletor);
}

void Mineanarchy::UtilityFunctions::runDeletors() {
    while(!deletors.empty()) {
        deletors.top()();
        deletors.pop();
    }
}

bool Mineanarchy::UtilityFunctions::readFile(const std::string& filename, std::vector<char>& buffer) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    size_t fileSize = (size_t) file.tellg();
    buffer.resize(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return true;
}
