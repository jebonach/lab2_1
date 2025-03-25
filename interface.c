#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "matrix.h"
#include "fieldinfo.h"
#include "real.h"
#include "complex.h"
#include "errors.h"

#define MAX_MATRICES 100

static Matrix* gMatrices[MAX_MATRICES];
static int gCount = 0;

static void addMatrixToStorage(Matrix* m) {
    if (gCount < MAX_MATRICES) {
        gMatrices[gCount++] = m;
    } else {
        printf("[Ошибка] Хранилище переполнено!\n");
        freeMatrix(m);
    }
}

static void removeMatrixFromStorage(int index) {
    if (index < 0 || index >= gCount) {
        printf("[Ошибка] Неверный индекс!\n");
        return;
    }
    freeMatrix(gMatrices[index]);
    for (int i = index; i < gCount - 1; i++) {
        gMatrices[i] = gMatrices[i+1];
    }
    gCount--;
}

static const char* getMatrixTypeName(const Matrix* M) {
    if (M->field == GetRealFieldInfo()) {
        return "Real";
    } else if (M->field == GetComplexFieldInfo()) {
        return "Complex";
    } else {
        return "Unknown";
    }
}

static void listAllMatrices() {
    printf("\n--- Список матриц (%d) ---\n", gCount);
    for (int i = 0; i < gCount; i++) {
        Matrix* M = gMatrices[i];
        if (!M) continue;
        const char* tname = getMatrixTypeName(M);

        printf("[%d] %dx%d (%s):\n", i, M->rows, M->cols, tname);
        printMatrix(M);
    }
    printf("-------------------------\n");
}

static FieldInfo* selectFieldInfo() {
    while (1) {
        printf("Выберите тип:\n");
        printf(" 1) вещественный (double)\n");
        printf(" 2) комплексный (double re, double im)\n");
        printf("> ");
        int choice;
        if (scanf("%d", &choice) == 1) {
            if (choice == 1) return GetRealFieldInfo();
            if (choice == 2) return GetComplexFieldInfo();
        }
        printf("[Ошибка] Введите 1 или 2.\n");
        while (getchar() != '\n') { }
    }
}

static void cmdCreateMatrix() {
    int rows, cols;
    printf("Введите число строк: ");
    scanf("%d", &rows);
    printf("Введите число столбцов: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0) {
        printf("[Ошибка] Неверные размеры.\n");
        return;
    }
    FieldInfo* fi = selectFieldInfo();
    Matrix* M = createMatrix(rows, cols, fi);

    ErrorCode err = readMatrix(M);
    if (!IsOk(&err)) {
        PrintError(&err);
        freeMatrix(M);
        return;
    }
    addMatrixToStorage(M);
    printf("Матрица сохранена под индексом #%d\n", gCount-1);
}

static void cmdRemoveMatrix() {
    int idx;
    printf("Введите индекс матрицы для удаления: ");
    scanf("%d", &idx);
    removeMatrixFromStorage(idx);
}

static void cmdPrintMatrix() {
    int idx;
    printf("Введите индекс матрицы: ");
    scanf("%d", &idx);
    if (idx < 0 || idx >= gCount) {
        printf("[Ошибка] Тут нет такого индекса(((\n");
        return;
    }
    printMatrix(gMatrices[idx]);
}

static void cmdAddMatrices() {
    int a,b;
    printf("Введите индекс матрицы A: ");
    scanf("%d", &a);
    printf("Введите индекс матрицы B: ");
    scanf("%d", &b);
    if (a<0 || a>=gCount || b<0 || b>=gCount) {
        printf("[Ошибка] Индексы вне диапазона.\n");
        return;
    }
    ErrorCode err;
    Matrix* C = addMatrix(gMatrices[a], gMatrices[b], &err);
    if (!C) {
        PrintError(&err);
        return;
    }
    addMatrixToStorage(C);
    printf("Результат сложения сохранён в #%d\n", gCount-1);
}

static void cmdMulMatrices() {
    int a,b;
    printf("Введите индекс матрицы A: ");
    scanf("%d", &a);
    printf("Введите индекс матрицы B: ");
    scanf("%d", &b);
    if (a<0 || a>=gCount || b<0 || b>=gCount) {
        printf("[Ошибка] Тут нет такого индекса(((\n");
        return;
    }
    ErrorCode err;
    Matrix* C = mulMatrix(gMatrices[a], gMatrices[b], &err);
    if (!C) {
        PrintError(&err);
        return;
    }
    addMatrixToStorage(C);
    printf("Результат умножения сохранён в #%d\n", gCount-1);
}

static void cmdMulScalar() {
    int a;
    double scal;
    printf("Введите индекс матрицы: ");
    scanf("%d", &a);
    if (a<0 || a>=gCount) {
        printf("[Ошибка] Тут нет такого индекса(((\n");
        return;
    }
    printf("Введите вещественный скаляр: ");
    scanf("%lf", &scal);

    ErrorCode err;
    Matrix* C = mulMatrixByScalar(gMatrices[a], scal, &err);
    if (!C) {
        PrintError(&err);
        return;
    }
    addMatrixToStorage(C);
    printf("Результат умножения на скаляр сохранён в #%d\n", gCount-1);
}

void runInterface() {
    while (1) {
        printf("\n=== МЕНЮ ===\n");
        printf("1) Создать матрицу\n");
        printf("2) Удалить матрицу\n");
        printf("3) Список матриц\n");
        printf("4) Вывести матрицу\n");
        printf("5) Сложить (A + B)\n");
        printf("6) Умножить (A * B)\n");
        printf("7) Умножить на скаляр\n");
        printf("0) Выход\n");
        printf("> ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("[Ошибка] Некорректный ввод.\n");
            while (getchar() != '\n') {}
            continue;
        }
        switch (choice) {
            case 1: cmdCreateMatrix(); break;
            case 2: cmdRemoveMatrix(); break;
            case 3: listAllMatrices(); break;
            case 4: cmdPrintMatrix(); break;
            case 5: cmdAddMatrices(); break;
            case 6: cmdMulMatrices(); break;
            case 7: cmdMulScalar(); break;
            case 0:
                printf("Это конечно, не молоток в ноут, но тоже выход\n");
                return;
            default:
                printf("[Ошибка] Нет такого пункта.\n");
        }
    }
}
