# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build

# Utility rule file for BUILD_DATA_GLTF_TEST.

# Include any custom commands dependencies for this target.
include test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/compiler_depend.make

# Include the progress variables for this target.
include test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/progress.make

test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST: temp/gltf_ruby_skeleton.ozz
test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST: temp/gltf_ruby_animation.ozz

temp/gltf_ruby_skeleton.ozz: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/gltf/sketchfab/ruby/scene.gltf
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ../../../../temp/gltf_ruby_skeleton.ozz, ../../../../temp/gltf_ruby_animation.ozz"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/animation/offline/gltf && ../../../../src/animation/offline/gltf/gltf2ozz --file=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/gltf/sketchfab/ruby/scene.gltf "--config={\"skeleton\":{\"filename\": \"/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/temp/gltf_ruby_skeleton.ozz\",\"import\":{\"enable\":true}},\"animations\":[{\"filename\":\"/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/temp/gltf_ruby_animation.ozz\"}]}"

temp/gltf_ruby_animation.ozz: temp/gltf_ruby_skeleton.ozz
	@$(CMAKE_COMMAND) -E touch_nocreate temp/gltf_ruby_animation.ozz

BUILD_DATA_GLTF_TEST: temp/gltf_ruby_animation.ozz
BUILD_DATA_GLTF_TEST: temp/gltf_ruby_skeleton.ozz
BUILD_DATA_GLTF_TEST: test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST
BUILD_DATA_GLTF_TEST: test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/build.make
.PHONY : BUILD_DATA_GLTF_TEST

# Rule to build all files generated by this target.
test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/build: BUILD_DATA_GLTF_TEST
.PHONY : test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/build

test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/clean:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/animation/offline/gltf && $(CMAKE_COMMAND) -P CMakeFiles/BUILD_DATA_GLTF_TEST.dir/cmake_clean.cmake
.PHONY : test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/clean

test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/depend:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/animation/offline/gltf /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/animation/offline/gltf /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/animation/offline/gltf/CMakeFiles/BUILD_DATA_GLTF_TEST.dir/depend
