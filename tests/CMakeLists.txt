# Поиск системной библиотеки Google Test
find_package(GTest REQUIRED)

add_executable(matrix_tests test_matrix.cpp ../src/matrix.cpp)

# Линковка с системными таргетами GTest
target_link_libraries(matrix_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(matrix_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME matrix_tests COMMAND matrix_tests)
