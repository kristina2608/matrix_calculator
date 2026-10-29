# CMake generated Testfile for 
# Source directory: /home/kristina/projects/matrix_calculator/tests
# Build directory: /home/kristina/projects/matrix_calculator/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[matrix_tests]=] "/home/kristina/projects/matrix_calculator/build/tests/matrix_tests")
set_tests_properties([=[matrix_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/kristina/projects/matrix_calculator/tests/CMakeLists.txt;12;add_test;/home/kristina/projects/matrix_calculator/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
