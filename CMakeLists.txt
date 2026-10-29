cmake_minimum_required(VERSION 3.20)
project(Matrix_Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение папки с заголовочными файлами
include_directories(include)

# Сборка основного исполняемого файла калькулятора
add_executable(matrix_calculator src/main.cpp src/matrix.cpp)

# Активация механизма тестов CTest
enable_testing()

# Подключение подпапки с тестами
add_subdirectory(tests)
