# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_look_at]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at/sample_look_at" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_look_at]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;49;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;0;")
add_test([=[sample_look_at_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at/sample_look_at" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--mesh=media/mesh.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_look_at_path1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;50;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;0;")
add_test([=[sample_look_at_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at/sample_look_at" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_look_at_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;51;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;0;")
add_test([=[sample_look_at_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at/sample_look_at" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_look_at_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;53;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;0;")
add_test([=[sample_look_at_invalid_mesh_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/look_at/sample_look_at" "--mesh=media/bad_mesh.ozz" "--norender")
set_tests_properties([=[sample_look_at_invalid_mesh_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;55;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/look_at/CMakeLists.txt;0;")
