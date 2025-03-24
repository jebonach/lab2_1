#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "matrix.h"
#include "fieldinfo.h"
#include "errors.h"

static int readInt(const char* prompt) {
    while (1) {
        printf("%s", prompt);
        int val;
        int rc = scanf("%d", &val);
        if (rc == 1) {
            return val;
        } else {
            printf("[Ошибка] Введите целое число.\n");
            while (getchar() != '\n') {}
        }
    }
}

static double readDouble(const char* prompt) {
    while (1) {
        printf("%s", prompt);
        double val;
        int rc = scanf("%lf", &val);
        if (rc == 1) {
            return val;
        } else {
            printf("[Ошибка] Введите вещественное число.\n");
            while (getchar() != '\n') { }
        }
    }
}

static FieldInfo* selectFieldInfo(const char* prompt) {
    while (1) {
        printf("%s\n", prompt);
        printf("1) Вещественные числа\n");
        printf("2) Комплексные числа\n");
        int choice;
        int rc = scanf("%d", &choice);
        if (rc == 1 && (choice == 1 || choice == 2)) {
            if (choice == 1) {
                return GetRealFieldInfo();
            } else {
                return GetComplexFieldInfo();
            }
        } else {
            printf("[Ошибка] Введите 1 или 2.\n");
            while (getchar() != '\n') { }
        }
    }
}

static Matrix* readUserMatrix(const char* matrixName) {
    printf("\n=== Создание матрицы %s ===\n", matrixName);
    FieldInfo* field = selectFieldInfo("Выберите тип для этой матрицы:");
    int rows = readInt("Введите число строк (m): ");
    int cols = readInt("Введите число столбцов (n): ");

    Matrix* mat = createMatrix(rows, cols, field);
    printf("Введите %d * %d элементов:\n", rows, cols);
    ErrorCode ec = readMatrix(mat);
    if (ec != ERROR_NONE) {
        printf("Ошибка ввода элементов матрицы: %s\n", GetErrorMessage(ec));
    }
    return mat;
}

void runInterface() {
    Matrix* M1 = readUserMatrix("M1");
    Matrix* M2 = readUserMatrix("M2");

    printf("\nВыберите операцию:\n");
    printf("1) Сложить M1 + M2\n");
    printf("2) Перемножить M1 * M2\n");
    printf("3) Умножить M1 на скаляр\n");
    printf("Введите (1/2/3): ");
    int op;
    while (scanf("%d", &op) != 1 || (op < 1 || op > 3)) {
        printf("[Ошибка] Введите 1, 2 или 3: ");
        while (getchar() != '\n') {}
    }

    ErrorCode err = ERROR_NONE;
    Matrix* result = NULL;

    if (op == 1) {
        result = addMatrix(M1, M2, &err);
        if (!result) {
            printf("Невозможно сложить матрицы: %s\n", GetErrorMessage(err));
        } else {
            printf("\nРезультат сложения (M1 + M2):\n");
            printMatrix(result);
        }
    } else if (op == 2) {
        result = mulMatrix(M1, M2, &err);
        if (!result) {
            printf("Невозможно умножить матрицы: %s\n", GetErrorMessage(err));
        } else {
            printf("\nРезультат умножения (M1 * M2):\n");
            printMatrix(result);
        }
    } else {
        double scalar = readDouble("Введите вещественный скаляр: ");
        result = mulMatrixByScalar(M1, scalar, &err);
        if (!result) {
            printf("Ошибка при умножении на скаляр: %s\n", GetErrorMessage(err));
        } else {
            printf("\nРезультат умножения (M1 * %.2lf):\n", scalar);
            printMatrix(result);
        }
    }

    freeMatrix(M1);
    freeMatrix(M2);
    freeMatrix(result);
}
