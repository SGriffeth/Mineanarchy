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

# Include any dependencies generated for this target.
include src/animation/offline/tools/CMakeFiles/dump2ozz.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/animation/offline/tools/CMakeFiles/dump2ozz.dir/compiler_depend.make

# Include the progress variables for this target.
include src/animation/offline/tools/CMakeFiles/dump2ozz.dir/progress.make

# Include the compile flags for this target's objects.
include src/animation/offline/tools/CMakeFiles/dump2ozz.dir/flags.make

src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o: src/animation/offline/tools/CMakeFiles/dump2ozz.dir/flags.make
src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/dump2ozz.cc
src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o: src/animation/offline/tools/CMakeFiles/dump2ozz.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o -MF CMakeFiles/dump2ozz.dir/dump2ozz.cc.o.d -o CMakeFiles/dump2ozz.dir/dump2ozz.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/dump2ozz.cc

src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dump2ozz.dir/dump2ozz.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/dump2ozz.cc > CMakeFiles/dump2ozz.dir/dump2ozz.cc.i

src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dump2ozz.dir/dump2ozz.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/dump2ozz.cc -o CMakeFiles/dump2ozz.dir/dump2ozz.cc.s

# Object files for target dump2ozz
dump2ozz_OBJECTS = \
"CMakeFiles/dump2ozz.dir/dump2ozz.cc.o"

# External object files for target dump2ozz
dump2ozz_EXTERNAL_OBJECTS =

src/animation/offline/tools/dump2ozz: src/animation/offline/tools/CMakeFiles/dump2ozz.dir/dump2ozz.cc.o
src/animation/offline/tools/dump2ozz: src/animation/offline/tools/CMakeFiles/dump2ozz.dir/build.make
src/animation/offline/tools/dump2ozz: src/animation/offline/tools/libozz_animation_tools.a
src/animation/offline/tools/dump2ozz: src/options/libozz_options.a
src/animation/offline/tools/dump2ozz: src/animation/offline/libozz_animation_offline.a
src/animation/offline/tools/dump2ozz: src/animation/runtime/libozz_animation.a
src/animation/offline/tools/dump2ozz: src/base/libozz_base.a
src/animation/offline/tools/dump2ozz: src/animation/offline/tools/json/libjson.a
src/animation/offline/tools/dump2ozz: src/animation/offline/tools/CMakeFiles/dump2ozz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dump2ozz"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dump2ozz.dir/link.txt --verbose=$(VERBOSE)
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && ./dump2ozz --file=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/dump2ozz.cc "--config={\"skeleton\": {\"import\":{\"enable\":false}},\"animations\":[]}" --config_dump_reference=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools/reference.json

# Rule to build all files generated by this target.
src/animation/offline/tools/CMakeFiles/dump2ozz.dir/build: src/animation/offline/tools/dump2ozz
.PHONY : src/animation/offline/tools/CMakeFiles/dump2ozz.dir/build

src/animation/offline/tools/CMakeFiles/dump2ozz.dir/clean:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools && $(CMAKE_COMMAND) -P CMakeFiles/dump2ozz.dir/cmake_clean.cmake
.PHONY : src/animation/offline/tools/CMakeFiles/dump2ozz.dir/clean

src/animation/offline/tools/CMakeFiles/dump2ozz.dir/depend:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/animation/offline/tools /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/animation/offline/tools/CMakeFiles/dump2ozz.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/animation/offline/tools/CMakeFiles/dump2ozz.dir/depend
