# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos
# Build directory: /home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[load_from_file]=] "/home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos/load_from_file" "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/media/bin/pab_skeleton.ozz")
set_tests_properties([=[load_from_file]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;10;add_test;/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;0;")
add_test([=[load_from_file_no_arg]=] "/home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos/load_from_file")
set_tests_properties([=[load_from_file_no_arg]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;11;add_test;/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;0;")
add_test([=[load_from_file_bad_arg]=] "/home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos/load_from_file" "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/media/bin/doesn_t_exist.ozz")
set_tests_properties([=[load_from_file_bad_arg]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;13;add_test;/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;0;")
add_test([=[custom_skeleton_importer]=] "/home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos/custom_skeleton_importer")
set_tests_properties([=[custom_skeleton_importer]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;25;add_test;/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;0;")
add_test([=[custom_animation_importer]=] "/home/sebastiang/prototypevulkangame/vulkantutorial/build/ozz-animation/howtos/custom_animation_importer")
set_tests_properties([=[custom_animation_importer]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;36;add_test;/home/sebastiang/prototypevulkangame/vulkantutorial/ozz-animation/howtos/CMakeLists.txt;0;")
