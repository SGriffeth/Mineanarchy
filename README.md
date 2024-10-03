To build on linux do:

cd build
cmake -S .. -B .

You will need the following libraries installed on your system: Vulkan, glfw3, nlhomann json, glm, and assimp
If you can't install them clone them into this proyect and modify the cmake to use add_subdirectory instead of find_package for linking to them

for running do (in build directory) ./vulkantutorial <game_directory> <mesh_file> <skeleton_file> <animation_file>

mesh_file, skeleton_file, and animation_file should be names of files in game_directory
