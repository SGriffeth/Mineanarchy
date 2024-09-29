#include <ma_UtilityFunctions.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdexcept>

std::stack<std::function<void()>> UtilityFunctions::deletors;
const char* UtilityFunctions::CONFIG_NAME = "maConf.json";
nlohmann::json UtilityFunctions::config;

int UtilityFunctions::queryConfigState() {
    std::vector<char> buffer;
    if(!readFile(std::string(CONFIG_NAME), buffer)) { // Determine if the file exists
        return CONFIG_INEXISTENT;
    }
    try {
        nlohmann::json parsedjs = nlohmann::json::parse(buffer.data());
    } catch (const std::exception& ex) {
        std::cerr << "Error parsing JSON: " << ex.what() << std::endl;
        return CONFIG_INVALIDLY_FORMATTED;
    }
    return CONFIG_READABLE;
}

void UtilityFunctions::getGameDirectory(std::string& gameDir) {
    gameDir = config["gameDir"];
}

std::string UtilityFunctions::getConfigValue(const char* name) {
    return config[name];
}

void UtilityFunctions::getConfig() {
    std::ifstream configFile(CONFIG_NAME);
    if (!configFile) {
        throw std::runtime_error("unable to open config");
    }

    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(configFile)),
        (std::istreambuf_iterator<char>())
    );
    try {
        config = nlohmann::json::parse(bytes.data());
    } catch (const std::exception& ex) {
        throw std::runtime_error("Error parsing JSON: " + std::string(ex.what()));
    }
    configFile.close();
}

void UtilityFunctions::createConfig() {
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

void UtilityFunctions::setGameDirectory(const char* name) {
    std::filesystem::create_directories(name);
    std::filesystem::create_directory(std::string(name) + "/shaders");
    config["gameDir"] = name;
}

void UtilityFunctions::setMeshFile(const char* name) {
    config["meshFile"] = name;
} 

void UtilityFunctions::setSkeletonFile(const char* name) {
    config["skeletonFile"] = name;  
} 

void UtilityFunctions::setAnimationFile(const char* name) {
    config["animationFile"] = name;
} 

void UtilityFunctions::writeToConfig() {
    std::ofstream configFile(CONFIG_NAME);
    configFile << config.dump() << std::endl;
    configFile.close();
}

VKAPI_ATTR VkBool32 VKAPI_CALL UtilityFunctions::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void UtilityFunctions::addDeletor(std::function<void()> deletor) {
    deletors.push(deletor);
}

void UtilityFunctions::runDeletors() {
    while(!deletors.empty()) {
        deletors.top()();
        deletors.pop();
    }
}

bool UtilityFunctions::readFile(const std::string& filename, std::vector<char>& buffer) {
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
