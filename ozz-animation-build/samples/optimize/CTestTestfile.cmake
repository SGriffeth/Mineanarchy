# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/optimize
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_optimize_default]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/optimize/sample_optimize" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_optimize_default]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;44;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;0;")
add_test([=[sample_optimize_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/optimize/sample_optimize" "--skeleton=media/skeleton.ozz" "--animation=media/animation_raw.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_optimize_path1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;45;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;0;")
add_test([=[sample_optimize_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/optimize/sample_optimize" "--skeleton=media/unexisting.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_optimize_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;46;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;0;")
add_test([=[sample_optimize_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/optimize/sample_optimize" "--animation=media/unexisting.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_optimize_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;48;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/optimize/CMakeLists.txt;0;")
