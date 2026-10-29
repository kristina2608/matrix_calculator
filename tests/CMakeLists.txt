cmake_minimum_required(VERSION 3.20)

# Поиск системной библиотеки Google Test
find_package(GTest REQUIRED)

add_executable(matrix_tests test_matrix.cpp ../src/matrix.cpp)

# Привязка системных библиотек GTest
target_link_libraries(matrix_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(matrix_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME matrix_tests COMMAND matrix_tests)
