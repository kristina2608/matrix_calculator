#include "matrix.h"
#include <stdio.h>
int main() {
 // Создание матриц
 Matrix A = create_matrix(2, 2);
 Matrix B = create_matrix(2, 2);
 // Заполнение данными
 A.data[0][0] = 1; A.data[0][1] = 2;
 A.data[1][0] = 3; A.data[1][1] = 4;

 B.data[0][0] = 5; B.data[0][1] = 6;
 B.data[1][0] = 7; B.data[1][1] = 8;
 // Операции
 Matrix sum = matrix_add(A, B);
 Matrix product = matrix_multiply(A, B);
 // Вывод результатов
 printf("Matrix A:\n");
 print_matrix(A);
 printf("Sum A+B:\n");
 print_matrix(sum);
 // Освобождение памяти
 free_matrix(A);
 free_matrix(B);
 free_matrix(sum);
 free_matrix(product);
 return 0;
}