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
include test/base/io/CMakeFiles/test_archive.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/base/io/CMakeFiles/test_archive.dir/compiler_depend.make

# Include the progress variables for this target.
include test/base/io/CMakeFiles/test_archive.dir/progress.make

# Include the compile flags for this target's objects.
include test/base/io/CMakeFiles/test_archive.dir/flags.make

test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o: test/base/io/CMakeFiles/test_archive.dir/flags.make
test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests.cc
test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o: test/base/io/CMakeFiles/test_archive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o -MF CMakeFiles/test_archive.dir/archive_tests.cc.o.d -o CMakeFiles/test_archive.dir/archive_tests.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests.cc

test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_archive.dir/archive_tests.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests.cc > CMakeFiles/test_archive.dir/archive_tests.cc.i

test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_archive.dir/archive_tests.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests.cc -o CMakeFiles/test_archive.dir/archive_tests.cc.s

test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o: test/base/io/CMakeFiles/test_archive.dir/flags.make
test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests_objects.cc
test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o: test/base/io/CMakeFiles/test_archive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o -MF CMakeFiles/test_archive.dir/archive_tests_objects.cc.o.d -o CMakeFiles/test_archive.dir/archive_tests_objects.cc.o -c /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests_objects.cc

test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_archive.dir/archive_tests_objects.cc.i"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests_objects.cc > CMakeFiles/test_archive.dir/archive_tests_objects.cc.i

test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_archive.dir/archive_tests_objects.cc.s"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io/archive_tests_objects.cc -o CMakeFiles/test_archive.dir/archive_tests_objects.cc.s

# Object files for target test_archive
test_archive_OBJECTS = \
"CMakeFiles/test_archive.dir/archive_tests.cc.o" \
"CMakeFiles/test_archive.dir/archive_tests_objects.cc.o"

# External object files for target test_archive
test_archive_EXTERNAL_OBJECTS =

test/base/io/test_archive: test/base/io/CMakeFiles/test_archive.dir/archive_tests.cc.o
test/base/io/test_archive: test/base/io/CMakeFiles/test_archive.dir/archive_tests_objects.cc.o
test/base/io/test_archive: test/base/io/CMakeFiles/test_archive.dir/build.make
test/base/io/test_archive: src/base/libozz_base.a
test/base/io/test_archive: test/gtest/libgtest.a
test/base/io/test_archive: test/base/io/CMakeFiles/test_archive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_archive"
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_archive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/base/io/CMakeFiles/test_archive.dir/build: test/base/io/test_archive
.PHONY : test/base/io/CMakeFiles/test_archive.dir/build

test/base/io/CMakeFiles/test_archive.dir/clean:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io && $(CMAKE_COMMAND) -P CMakeFiles/test_archive.dir/cmake_clean.cmake
.PHONY : test/base/io/CMakeFiles/test_archive.dir/clean

test/base/io/CMakeFiles/test_archive.dir/depend:
	cd /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/io /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/io/CMakeFiles/test_archive.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/base/io/CMakeFiles/test_archive.dir/depend
