# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_user_channel]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel/sample_user_channel" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_user_channel]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;48;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;0;")
add_test([=[sample_user_channel_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel/sample_user_channel" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_user_channel_path1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;49;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;0;")
add_test([=[sample_user_channel_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel/sample_user_channel" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_user_channel_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;50;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;0;")
add_test([=[sample_user_channel_invalid_animation_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel/sample_user_channel" "--animation=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_user_channel_invalid_animation_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;52;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;0;")
add_test([=[sample_user_channel_invalid_track_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/user_channel/sample_user_channel" "--track=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_user_channel_invalid_track_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;54;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/user_channel/CMakeLists.txt;0;")
