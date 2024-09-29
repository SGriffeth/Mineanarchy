# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/attach
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_attach]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/attach/sample_attach" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_attach]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;44;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;0;")
add_test([=[sample_attach_load_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/attach/sample_attach" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_attach_load_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;45;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;0;")
add_test([=[sample_attach_load_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/attach/sample_attach" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_attach_load_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;46;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;0;")
add_test([=[sample_attach_load_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/attach/sample_attach" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_attach_load_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;48;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/attach/CMakeLists.txt;0;")
