# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/playback
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_playback]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/playback/sample_playback" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_playback]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;44;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;0;")
add_test([=[sample_playback_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/playback/sample_playback" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_playback_path1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;45;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;0;")
add_test([=[sample_playback_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/playback/sample_playback" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_playback_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;46;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;0;")
add_test([=[sample_playback_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/playback/sample_playback" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_playback_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;48;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/playback/CMakeLists.txt;0;")
