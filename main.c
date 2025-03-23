#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "real.h"
#include "complex.h"

static void runTests() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2, rf);
    Matrix* B = createMatrix(2, rf);

    double valsA[4] = {1, 2, 3, 4};
    double valsB[4] = {5, 6, 7, 8};
    for(int i = 0; i < 4; i++){
        rf->freeValue(A->data[i]);
        rf->freeValue(B->data[i]);
        double* va = malloc(sizeof(double));
        double* vb = malloc(sizeof(double));
        *va = valsA[i];
        *vb = valsB[i];
        A->data[i] = va;
        B->data[i] = vb;
    }

    Matrix* C = addMatrix(A, B);
    double cExpectedAdd[4] = {6, 8, 10, 12};
    for(int i=0; i<4; i++){
        double got = *((double*)C->data[i]);
        assert(got == cExpectedAdd[i]);
    }
    freeMatrix(C);

    C = mulMatrix(A, B);
    double cExpectedMul[4] = {19, 22, 43, 50};
    for(int i=0; i<4; i++){
        double got = *((double*)C->data[i]);
        assert(got == cExpectedMul[i]);
    }
    freeMatrix(C);

    C = mulMatrixByScalar(A, 10.0);
    double cExpectedScalar[4] = {10, 20, 30, 40};
    for(int i=0; i<4; i++){
        double got = *((double*)C->data[i]);
        assert(got == cExpectedScalar[i]);
    }
    freeMatrix(C);

    freeMatrix(A);
    freeMatrix(B);

    printf("Все базовые unit-тесты для вещественных чисел прошли успешно!\n");
}


static void runSession() {
    printf("\nВыберите тип матрицы:\n");
    printf("1) вещественные числа\n");
    printf("2) комплексные числа\n");
    printf("Введите число (1 или 2): ");

    int choice;
    while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        // Ошибочный ввод
        printf("[Ошибка] Введите 1 или 2: ");
        // очистим буфер ввода
        while (getchar() != '\n') { /* пустой цикл */ }
    }

    FieldInfo* field = NULL;
    if (choice == 1) {
        field = GetRealFieldInfo();
        printf("Режим вещественных чисел.\n");
        printf("Для ввода каждого элемента нужно ввести 1 число.\n");
    } else {
        field = GetComplexFieldInfo();
        printf("Режим комплексных чисел.\n");
        printf("Для ввода каждого элемента введите 2 числа (Re Im).\n");
    }

    printf("Введите размер матрицы n (квадратная): ");
    int n;
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("[Ошибка] Введите положительное целое число n: ");
        while (getchar() != '\n') { /* чистим буфер */ }
    }

    Matrix* M1 = createMatrix(n, field);
    Matrix* M2 = createMatrix(n, field);

    printf("Введите матрицу M1 (n*n элементов):\n");
    readMatrix(M1);

    printf("Введите матрицу M2 (n*n элементов):\n");
    readMatrix(M2);

    printf("M1:\n");
    printMatrix(M1);
    printf("M2:\n");
    printMatrix(M2);

    Matrix* Msum = addMatrix(M1, M2);
    printf("M1 + M2:\n");
    printMatrix(Msum);

    Matrix* Mmul = mulMatrix(M1, M2);
    printf("M1 * M2:\n");
    printMatrix(Mmul);

    printf("Введите вещественный скаляр (даже если числа комплексные, скаляр - вещественный): ");
    double scalar;
    while (scanf("%lf", &scalar) != 1) {
        printf("[Ошибка] Введите корректное вещественное число: ");
        while (getchar() != '\n') {}
    }
    Matrix* Mscal = mulMatrixByScalar(M1, scalar);
    printf("M1 * %.4lf:\n", scalar);
    printMatrix(Mscal);

    freeMatrix(M1);
    freeMatrix(M2);
    freeMatrix(Msum);
    freeMatrix(Mmul);
    freeMatrix(Mscal);
}

int main() {
    runTests();
    runSession();
    return 0;
}
