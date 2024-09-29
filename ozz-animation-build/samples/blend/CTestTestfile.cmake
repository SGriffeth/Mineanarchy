# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_blend]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_blend]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;55;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
add_test([=[sample_blend_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--skeleton=media/skeleton.ozz" "--animation1=media/animation1.ozz" "--animation2=media/animation2.ozz" "--animation3=media/animation3.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_blend_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;56;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
add_test([=[sample_blend_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_blend_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;57;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
add_test([=[sample_blend_invalid_animation_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--animation1=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_blend_invalid_animation_path1]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;59;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
add_test([=[sample_blend_invalid_animation_path2]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--animation2=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_blend_invalid_animation_path2]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;61;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
add_test([=[sample_blend_invalid_animation_path3]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/blend/sample_blend" "--animation3=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_blend_invalid_animation_path3]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;63;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/blend/CMakeLists.txt;0;")
