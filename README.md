# Калькулятор матриц (Matrix Calculator)

Проект представляет собой библиотеку на C++17 для работы с динамическими матрицами, выделяемыми в куче. Проект полностью протестирован с помощью Google Test и профилирован на предмет утечек памяти через Valgrind.

## 🛠️ Инструкция по сборке и запуску

Для сборки проекта необходимы компилятор с поддержкой C++17 и утилита CMake (версии 3.20 или выше).

### Локальная сборка в системе:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Запуск модульных тестов:
```bash
cd build && ctest --verbose
```

### Проверка утечек памяти (Valgrind):
```bash
valgrind --leak-check=full --error-exitcode=1 ./build/tests/matrix_tests
```

### Сборка и запуск через Docker:
```bash
docker build -t matrix-calculator .
docker run -it --rm matrix-calculator
```

## ⚠️ Способ обработки ошибок
В проекте выбран **подход с использованием исключений** (`Exceptions`), соответствующий стандартам C++ интерфейсов. При обнаружении некорректных параметров функции выбрасывают исключения `std::invalid_argument` или `std::bad_alloc`, предотвращая неопределенное поведение (UB) и аварийное завершение программы (`segfault`).

## 📋 Реализованные функции

- `Matrix create_matrix(int rows, int cols)` — Выделение памяти в куче и создание нулевой матрицы.
- `void free_matrix(Matrix m)` — Безопасное поэлементное освобождение динамической памяти.
- `Matrix matrix_copy(Matrix original)` — Глубокое копирование матрицы в новый блок памяти.
- `Matrix matrix_from_array(const double* data, int rows, int cols)` — Импорт данных из одномерного массива.
- `Matrix matrix_add(Matrix a, Matrix b)` — Поэлементное сложение двух матриц.
- `Matrix matrix_multiply(Matrix a, Matrix b)` — Оптимизированное кэш-последовательное умножение матриц.
- `Matrix matrix_transpose(Matrix a)` — Транспонирование (поворот) матрицы.
- `void print_matrix(Matrix m)` — Форматированный вывод матриц с автоматическим сокращением больших размеров.

## 🧪 Перечень проверяемых сценариев (Google Test)

1. **MatrixTest.CreateMatrix_NormalCase** — Корректное выделение памяти и заполнение нулями.
2. **MatrixTest.Addition_NormalCase** — Математическая точность сложения матриц 2×2.
3. **MatrixTest.Multiplication_NormalCase** — Математическая точность умножения матриц 2×2.
4. **MatrixTest.Transpose_NormalCase** — Корректность перестановки строк и столбцов матрицы.
5. **MatrixTest.CreateMatrix_MinimumSize** — Граничный случай: создание минимальной матрицы размера 1×1.
6. **MatrixTest.Multiplication_RowTimesColumn_1x1** — Граничный случай: умножение строки на столбец с результатом 1×1.
7. **MatrixTest.TransposeTwice_ReturnsOriginal** — Логическая проверка: двойное транспонирование возвращает исходную матрицу.
8. **MatrixTest.CreateMatrix_ZeroRows** / **NegativeCols** — Обработка ошибок: попытка создать матрицу с некорректными размерами.
9. **MatrixTest.Addition_SizeMismatch** / **Multiplication_SizeMismatch** — Обработка ошибок при несовпадении размерностей.
10. **MatrixTest.FreeMatrix_EmptyIsSafe** — Граничный случай: защита от двойного освобождения и безопасность удаления пустой структуры (`nullptr`).

## 📊 Пример входных и выходных данных

Пример работы функции `matrix_multiply` для матриц \(A\) (\(2 \times 3\)) и \(B\) (\(3 \times 2\)):

**Входные данные:**
```text
Матрица А [2x3]:
[  1.00   2.00   3.00]
[  4.00   5.00   6.00]

Матрица B [3x2]:
[  7.00   8.00]
[  9.00  10.00]
[ 11.00  12.00]
```

**Выходные данные (Результат умножения \(A \times B\) [2x2]):**
```text
[ 58.00  64.00]
[139.00 154.00]
```
