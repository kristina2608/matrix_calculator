#include "matrix.h"

#include <iomanip>
#include <iostream>
Matrix create_matrix(int rows, int cols) {
    // 1. Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    // 2. Выделение памяти для массива указателей
    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }
    // 3. Выделение памяти для каждой строки
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            // Освобождение уже выделенной памяти при ошибке
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        // 4. Инициализация нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }
    return mat;
}

void free_matrix(Matrix m) {
    // 1. Проверка на nullptr - защита от двойного освобождения
    if (m.data == nullptr) {
        return;
    }
    // 2. Освобождение памяти каждой строки
    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];   // Освобождаем строку
            m.data[i] = nullptr;  // Обнуляем указатель
        }
    }
    // 3. Освобождение массива указателей
    delete[] m.data;
    // 4. Обнуление структуры (защита от use-after-free)
    m.data = nullptr;
    m.rows = 0;
    m.cols = 0;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument(
            "Matrix dimensions are incompatible for multiplication (columns of A must equal rows "
            "of B)");
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int k = 0; k < a.cols; k++) {
            double factor = a.data[i][k];

            // Последовательный обход по строке матрицы B минимизирует промахи кэша (Cache Misses)
            for (int j = 0; j < b.cols; j++) {
                result.data[i][j] += factor * b.data[k][j];
            }
        }
    }

    return result;
}

void print_matrix(Matrix m) {
    // 1. Проверка валидности матрицы
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }
    // 2. Настройка формата вывода
    std::cout << std::fixed << std::setprecision(2);
    // 3. Проверка необходимости сокращения вывода
    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW || m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;
    // 4. Вывод матрицы
    for (int i = 0; i < rows_to_show; i++) {
        // Пропуск средних строк для больших матриц
        if (show_summary && i == MAX_ROWS_TO_SHOW / 2 && m.rows > MAX_ROWS_TO_SHOW) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - 2; j++) {
                std::cout << " ";  // 6 пробелов под число
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "[";  // Открывающая скобка
        // Вывод элементов строки
        for (int j = 0; j < cols_to_show; j++) {
            // Пропуск средних столбцов для больших матриц
            if (show_summary && j == MAX_COLS_TO_SHOW / 2 && m.cols > MAX_COLS_TO_SHOW) {
                std::cout << " ... ";
                continue;
            }
            std::cout << std::setw(6) << m.data[i][j];  // Выравнивание

            if (j < cols_to_show - 1) {
                std::cout << " ";  // Пробел между элементами
            }
        }
        std::cout << "]";  // Закрывающая скобка
        // Добавление многоточия если пропущены столбцы
        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }

        std::cout << std::endl;
    }
    // 5. Добавление многоточия если пропущены строки
    if (show_summary && m.rows > MAX_ROWS_TO_SHOW) {
        std::cout << "[...";
        for (int j = 0; j < std::min(cols_to_show, m.cols); j++) {
            std::cout << " ... ";
        }
        std::cout << "...]" << std::endl;
    }
    // 6. Информация о размере если матрица большая
    if (show_summary) {
        std::cout << "Matrix " << m.rows << "×" << m.cols << " (showing first " << rows_to_show
                  << "×" << cols_to_show << ")" << std::endl;
    }
}

Matrix matrix_from_array(const double* data, int rows, int cols) {
    // 1. Проверка на корректность входных данных
    if (data == nullptr) {
        throw std::invalid_argument("Input data pointer must not be nullptr");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    // 2. Выделяем память под новую матрицу с помощью create_matrix
    Matrix result = create_matrix(rows, cols);

    // 3. Копируем данные из одномерного массива в двумерный
    // Формула индекса для одномерного массива: [i * cols + j]
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i * cols + j];
        }
    }

    return result;
}
// Функция глубокого копирования матрицы
Matrix matrix_copy(Matrix original) {
    // 1. Защита от передачи неинициализированной структуры
    if (original.data == nullptr) {
        throw std::invalid_argument("Cannot copy a matrix with nullptr data pointer");
    }

    // 2. Создаем новую матрицу с точно такими же размерами
    // С помощью функции create_matrix выделяется новый независимый блок памяти в куче
    Matrix copy = create_matrix(original.rows, original.cols);

    // 3. Поэлементно копируем данные из оригинала в новую матрицу
    for (int i = 0; i < copy.rows; i++) {
        for (int j = 0; j < copy.cols; j++) {
            copy.data[i][j] = original.data[i][j];
        }
    }

    // 4. Возвращаем полностью независимую копию
    return copy;
}

Matrix matrix_transpose(Matrix a) {
    // 1. Проверяем валидность исходной матрицы
    if (a.data == nullptr || a.rows <= 0 || a.cols <= 0) {
        throw std::invalid_argument("Cannot transpose an empty or uninitialized matrix");
    }

    // 2. Создаем матрицу с «перевернутыми» размерами (строки меняются со столбцами)
    Matrix result = create_matrix(a.cols, a.rows);

    // 3. Переносим элементы: строка становится столбцом, столбец — строкой
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }

    // 4. Возвращаем транспонированную матрицу
    return result;
}
