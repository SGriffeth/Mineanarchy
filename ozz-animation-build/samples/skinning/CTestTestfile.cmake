# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_skinning]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning/sample_skinning" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_skinning]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;49;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;0;")
add_test([=[sample_skinning_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning/sample_skinning" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--mesh=media/mesh.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_skinning_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;50;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;0;")
add_test([=[sample_skinning_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning/sample_skinning" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_skinning_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;51;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;0;")
add_test([=[sample_skinning_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning/sample_skinning" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_skinning_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;53;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;0;")
add_test([=[sample_skinning_invalid_mesh_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/skinning/sample_skinning" "--mesh=media/bad_mesh.ozz" "--norender")
set_tests_properties([=[sample_skinning_invalid_mesh_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;55;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/skinning/CMakeLists.txt;0;")
