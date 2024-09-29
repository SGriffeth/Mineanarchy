# CMake generated Testfile for 
# Source directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread
# Build directory: /home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sample_multithread]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread/sample_multithread" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_multithread]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;57;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;0;")
add_test([=[sample_multithread_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread/sample_multithread" "--skeleton=media/skeleton.ozz" "--animation=media/animation.ozz" "--max_idle_loops=20" "--norender")
set_tests_properties([=[sample_multithread_path]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;58;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;0;")
add_test([=[sample_multithread_invalid_skeleton_path]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread/sample_multithread" "--skeleton=media/bad_skeleton.ozz" "--norender")
set_tests_properties([=[sample_multithread_invalid_skeleton_path]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;59;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;0;")
add_test([=[sample_multithread_invalid_animation_path1]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread/sample_multithread" "--animation1=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_multithread_invalid_animation_path1]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;61;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;0;")
add_test([=[sample_multithread_invalid_animation_path2]=] "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation-build/samples/multithread/sample_multithread" "--animation2=media/bad_animation.ozz" "--norender")
set_tests_properties([=[sample_multithread_invalid_animation_path2]=] PROPERTIES  WILL_FAIL "true" _BACKTRACE_TRIPLES "/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;63;add_test;/home/sebastiang/prototypevulkangame/Mineanarchy/ozz-animation/samples/multithread/CMakeLists.txt;0;")
