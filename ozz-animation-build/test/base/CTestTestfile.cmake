# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_endianness]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/test_endianness")
set_tests_properties([=[test_endianness]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;11;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;0;")
add_test([=[test_log]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/test_log")
set_tests_properties([=[test_log]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;19;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;0;")
add_test([=[test_platform]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/test_platform")
set_tests_properties([=[test_platform]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;29;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;0;")
add_test([=[test_fuse_base]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/test/base/test_fuse_base")
set_tests_properties([=[test_fuse_base]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;44;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/test/base/CMakeLists.txt;0;")
subdirs("containers")
subdirs("io")
subdirs("maths")
subdirs("memory")
