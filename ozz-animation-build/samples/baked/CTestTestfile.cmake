# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/baked
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_baked]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/baked/sample_baked" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_baked]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;47;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;0;")
add_test([=[sample_baked_load_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/baked/sample_baked" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_baked_load_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;48;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;0;")
add_test([=[sample_baked_load_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/baked/sample_baked" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_baked_load_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;49;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;0;")
add_test([=[sample_baked_load_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/baked/sample_baked" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_baked_load_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;51;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/baked/CMakeLists.txt;0;")
