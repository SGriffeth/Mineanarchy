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
include src/base/CMakeFiles/ozz_base.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/base/CMakeFiles/ozz_base.dir/compiler_depend.make

# Include the progress variables for this target.
include src/base/CMakeFiles/ozz_base.dir/progress.make

# Include the compile flags for this target's objects.
include src/base/CMakeFiles/ozz_base.dir/flags.make

src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/memory/allocator.cc
src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o -MF CMakeFiles/ozz_base.dir/memory/allocator.cc.o.d -o CMakeFiles/ozz_base.dir/memory/allocator.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/memory/allocator.cc

src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/memory/allocator.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/memory/allocator.cc > CMakeFiles/ozz_base.dir/memory/allocator.cc.i

src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/memory/allocator.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/memory/allocator.cc -o CMakeFiles/ozz_base.dir/memory/allocator.cc.s

src/base/CMakeFiles/ozz_base.dir/platform.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/platform.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/platform.cc
src/base/CMakeFiles/ozz_base.dir/platform.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/base/CMakeFiles/ozz_base.dir/platform.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/platform.cc.o -MF CMakeFiles/ozz_base.dir/platform.cc.o.d -o CMakeFiles/ozz_base.dir/platform.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/platform.cc

src/base/CMakeFiles/ozz_base.dir/platform.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/platform.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/platform.cc > CMakeFiles/ozz_base.dir/platform.cc.i

src/base/CMakeFiles/ozz_base.dir/platform.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/platform.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/platform.cc -o CMakeFiles/ozz_base.dir/platform.cc.s

src/base/CMakeFiles/ozz_base.dir/log.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/log.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/log.cc
src/base/CMakeFiles/ozz_base.dir/log.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/base/CMakeFiles/ozz_base.dir/log.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/log.cc.o -MF CMakeFiles/ozz_base.dir/log.cc.o.d -o CMakeFiles/ozz_base.dir/log.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/log.cc

src/base/CMakeFiles/ozz_base.dir/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/log.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/log.cc > CMakeFiles/ozz_base.dir/log.cc.i

src/base/CMakeFiles/ozz_base.dir/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/log.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/log.cc -o CMakeFiles/ozz_base.dir/log.cc.s

src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/containers/string_archive.cc
src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o -MF CMakeFiles/ozz_base.dir/containers/string_archive.cc.o.d -o CMakeFiles/ozz_base.dir/containers/string_archive.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/containers/string_archive.cc

src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/containers/string_archive.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/containers/string_archive.cc > CMakeFiles/ozz_base.dir/containers/string_archive.cc.i

src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/containers/string_archive.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/containers/string_archive.cc -o CMakeFiles/ozz_base.dir/containers/string_archive.cc.s

src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/archive.cc
src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o -MF CMakeFiles/ozz_base.dir/io/archive.cc.o.d -o CMakeFiles/ozz_base.dir/io/archive.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/archive.cc

src/base/CMakeFiles/ozz_base.dir/io/archive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/io/archive.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/archive.cc > CMakeFiles/ozz_base.dir/io/archive.cc.i

src/base/CMakeFiles/ozz_base.dir/io/archive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/io/archive.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/archive.cc -o CMakeFiles/ozz_base.dir/io/archive.cc.s

src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/stream.cc
src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o -MF CMakeFiles/ozz_base.dir/io/stream.cc.o.d -o CMakeFiles/ozz_base.dir/io/stream.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/stream.cc

src/base/CMakeFiles/ozz_base.dir/io/stream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/io/stream.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/stream.cc > CMakeFiles/ozz_base.dir/io/stream.cc.i

src/base/CMakeFiles/ozz_base.dir/io/stream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/io/stream.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/io/stream.cc -o CMakeFiles/ozz_base.dir/io/stream.cc.s

src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/box.cc
src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o -MF CMakeFiles/ozz_base.dir/maths/box.cc.o.d -o CMakeFiles/ozz_base.dir/maths/box.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/box.cc

src/base/CMakeFiles/ozz_base.dir/maths/box.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/maths/box.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/box.cc > CMakeFiles/ozz_base.dir/maths/box.cc.i

src/base/CMakeFiles/ozz_base.dir/maths/box.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/maths/box.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/box.cc -o CMakeFiles/ozz_base.dir/maths/box.cc.s

src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math.cc
src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o -MF CMakeFiles/ozz_base.dir/maths/simd_math.cc.o.d -o CMakeFiles/ozz_base.dir/maths/simd_math.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math.cc

src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/maths/simd_math.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math.cc > CMakeFiles/ozz_base.dir/maths/simd_math.cc.i

src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/maths/simd_math.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math.cc -o CMakeFiles/ozz_base.dir/maths/simd_math.cc.s

src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/math_archive.cc
src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o -MF CMakeFiles/ozz_base.dir/maths/math_archive.cc.o.d -o CMakeFiles/ozz_base.dir/maths/math_archive.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/math_archive.cc

src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/maths/math_archive.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/math_archive.cc > CMakeFiles/ozz_base.dir/maths/math_archive.cc.i

src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/maths/math_archive.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/math_archive.cc -o CMakeFiles/ozz_base.dir/maths/math_archive.cc.s

src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/soa_math_archive.cc
src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o -MF CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o.d -o CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/soa_math_archive.cc

src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/soa_math_archive.cc > CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.i

src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/soa_math_archive.cc -o CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.s

src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/flags.make
src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math_archive.cc
src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o: src/base/CMakeFiles/ozz_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o -MF CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o.d -o CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math_archive.cc

src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math_archive.cc > CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.i

src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base/maths/simd_math_archive.cc -o CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.s

# Object files for target ozz_base
ozz_base_OBJECTS = \
"CMakeFiles/ozz_base.dir/memory/allocator.cc.o" \
"CMakeFiles/ozz_base.dir/platform.cc.o" \
"CMakeFiles/ozz_base.dir/log.cc.o" \
"CMakeFiles/ozz_base.dir/containers/string_archive.cc.o" \
"CMakeFiles/ozz_base.dir/io/archive.cc.o" \
"CMakeFiles/ozz_base.dir/io/stream.cc.o" \
"CMakeFiles/ozz_base.dir/maths/box.cc.o" \
"CMakeFiles/ozz_base.dir/maths/simd_math.cc.o" \
"CMakeFiles/ozz_base.dir/maths/math_archive.cc.o" \
"CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o" \
"CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o"

# External object files for target ozz_base
ozz_base_EXTERNAL_OBJECTS =

src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/memory/allocator.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/platform.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/log.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/containers/string_archive.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/io/archive.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/io/stream.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/maths/box.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/maths/simd_math.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/maths/math_archive.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/maths/soa_math_archive.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/maths/simd_math_archive.cc.o
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/build.make
src/base/libozz_base.a: src/base/CMakeFiles/ozz_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libozz_base.a"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/ozz_base.dir/cmake_clean_target.cmake
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ozz_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/base/CMakeFiles/ozz_base.dir/build: src/base/libozz_base.a
.PHONY : src/base/CMakeFiles/ozz_base.dir/build

src/base/CMakeFiles/ozz_base.dir/clean:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/ozz_base.dir/cmake_clean.cmake
.PHONY : src/base/CMakeFiles/ozz_base.dir/clean

src/base/CMakeFiles/ozz_base.dir/depend:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/src/base /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/src/base/CMakeFiles/ozz_base.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/base/CMakeFiles/ozz_base.dir/depend
