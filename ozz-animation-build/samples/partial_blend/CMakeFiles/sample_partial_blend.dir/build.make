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
include samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include samples/partial_blend/CMakeFiles/sample_partial_blend.dir/compiler_depend.make

# Include the progress variables for this target.
include samples/partial_blend/CMakeFiles/sample_partial_blend.dir/progress.make

# Include the compile flags for this target's objects.
include samples/partial_blend/CMakeFiles/sample_partial_blend.dir/flags.make

samples/partial_blend/README.md: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/README.md
samples/partial_blend/README.md: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_skeleton.ozz
samples/partial_blend/README.md: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_walk.ozz
samples/partial_blend/README.md: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_crossarms.ozz
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating README.md, media/skeleton.ozz, media/animation_base.ozz, media/animation_partial.ozz"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/cmake -E make_directory media
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/cmake -E copy /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/README.md .
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/cmake -E copy /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_skeleton.ozz ./media/skeleton.ozz
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/cmake -E copy /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_walk.ozz ./media/animation_base.ozz
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/cmake -E copy /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/media/bin/pab_crossarms.ozz ./media/animation_partial.ozz

samples/partial_blend/media/skeleton.ozz: samples/partial_blend/README.md
	@$(CMAKE_COMMAND) -E touch_nocreate samples/partial_blend/media/skeleton.ozz

samples/partial_blend/media/animation_base.ozz: samples/partial_blend/README.md
	@$(CMAKE_COMMAND) -E touch_nocreate samples/partial_blend/media/animation_base.ozz

samples/partial_blend/media/animation_partial.ozz: samples/partial_blend/README.md
	@$(CMAKE_COMMAND) -E touch_nocreate samples/partial_blend/media/animation_partial.ozz

samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o: samples/partial_blend/CMakeFiles/sample_partial_blend.dir/flags.make
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/sample_partial_blend.cc
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o: samples/partial_blend/CMakeFiles/sample_partial_blend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o -MF CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o.d -o CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/sample_partial_blend.cc

samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/sample_partial_blend.cc > CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.i

samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend/sample_partial_blend.cc -o CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.s

# Object files for target sample_partial_blend
sample_partial_blend_OBJECTS = \
"CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o"

# External object files for target sample_partial_blend
sample_partial_blend_EXTERNAL_OBJECTS =

samples/partial_blend/sample_partial_blend: samples/partial_blend/CMakeFiles/sample_partial_blend.dir/sample_partial_blend.cc.o
samples/partial_blend/sample_partial_blend: samples/partial_blend/CMakeFiles/sample_partial_blend.dir/build.make
samples/partial_blend/sample_partial_blend: samples/framework/libsample_framework.a
samples/partial_blend/sample_partial_blend: samples/framework/glfw/libglfw.a
samples/partial_blend/sample_partial_blend: /usr/lib/libGL.so
samples/partial_blend/sample_partial_blend: /usr/lib/libGLU.so
samples/partial_blend/sample_partial_blend: /usr/lib/libSM.so
samples/partial_blend/sample_partial_blend: /usr/lib/libICE.so
samples/partial_blend/sample_partial_blend: /usr/lib/libX11.so
samples/partial_blend/sample_partial_blend: /usr/lib/libXext.so
samples/partial_blend/sample_partial_blend: src/geometry/runtime/libozz_geometry.a
samples/partial_blend/sample_partial_blend: src/animation/offline/libozz_animation_offline.a
samples/partial_blend/sample_partial_blend: src/animation/runtime/libozz_animation.a
samples/partial_blend/sample_partial_blend: src/options/libozz_options.a
samples/partial_blend/sample_partial_blend: src/base/libozz_base.a
samples/partial_blend/sample_partial_blend: samples/partial_blend/CMakeFiles/sample_partial_blend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sample_partial_blend"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample_partial_blend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/build: samples/partial_blend/sample_partial_blend
.PHONY : samples/partial_blend/CMakeFiles/sample_partial_blend.dir/build

samples/partial_blend/CMakeFiles/sample_partial_blend.dir/clean:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend && $(CMAKE_COMMAND) -P CMakeFiles/sample_partial_blend.dir/cmake_clean.cmake
.PHONY : samples/partial_blend/CMakeFiles/sample_partial_blend.dir/clean

samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend: samples/partial_blend/README.md
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend: samples/partial_blend/media/animation_base.ozz
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend: samples/partial_blend/media/animation_partial.ozz
samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend: samples/partial_blend/media/skeleton.ozz
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/partial_blend /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/partial_blend/CMakeFiles/sample_partial_blend.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : samples/partial_blend/CMakeFiles/sample_partial_blend.dir/depend
