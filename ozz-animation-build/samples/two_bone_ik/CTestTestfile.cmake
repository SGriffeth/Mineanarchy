# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/two_bone_ik
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_two_bone_ik]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/two_bone_ik/sample_two_bone_ik" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_two_bone_ik]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;41;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;0;")
add_test([=[sample_two_bone_ik_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/two_bone_ik/sample_two_bone_ik" "--skeleton=media/skeleton.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_two_bone_ik_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;42;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;0;")
add_test([=[sample_two_bone_ik_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/two_bone_ik/sample_two_bone_ik" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_two_bone_ik_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;43;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/two_bone_ik/CMakeLists.txt;0;")
