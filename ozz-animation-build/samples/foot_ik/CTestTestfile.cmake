# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_foot_ik]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik/sample_foot_ik" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_foot_ik]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;53;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;0;")
add_test([=[sample_foot_ik_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik/sample_foot_ik" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--mesh=media/mesh.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_foot_ik_path1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;54;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;0;")
add_test([=[sample_foot_ik_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik/sample_foot_ik" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_foot_ik_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;55;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;0;")
add_test([=[sample_foot_ik_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik/sample_foot_ik" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_foot_ik_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;57;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;0;")
add_test([=[sample_foot_ik_invalid_mesh_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/foot_ik/sample_foot_ik" "--mesh=media/bad_mesh.ozz" "--norender")
set_tests_properties([=[sample_foot_ik_invalid_mesh_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;59;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/foot_ik/CMakeLists.txt;0;")
