#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

Matrix* createMatrix(int rows, int cols, FieldInfo* field) {
    Matrix* mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->field = field;
    mat->data = malloc(rows * cols * sizeof(void*));

    for (int i = 0; i < rows * cols; i++) {
        mat->data[i] = field->createZero();
    }
    return mat;
}

void freeMatrix(Matrix* mat) {
    if (!mat) return;
    int total = mat->rows * mat->cols;
    for (int i = 0; i < total; i++) {
        mat->field->freeValue(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

ErrorCode readMatrix(Matrix* mat) {
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        mat->field->freeValue(mat->data[i]);
        mat->data[i] = mat->field->readValue();
    }
    return MakeError(ERROR_NONE, "OK");
}

void printMatrix(const Matrix* mat) {
    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            mat->field->printValue(mat->data[r * mat->cols + c]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* addMatrix(const Matrix* A, const Matrix* B, ErrorCode* err) {
    *err = MakeError(ERROR_NONE, "OK");
    if (A->field != B->field) {
        *err = MakeError(ERROR_TYPE, "Разные типы элементов");
        return NULL;
    }
    if (A->rows != B->rows || A->cols != B->cols) {
        *err = MakeError(ERROR_DIM, "Несовместимые размеры при сложении");
        return NULL;
    }
    Matrix* C = createMatrix(A->rows, A->cols, A->field);
    int total = A->rows * A->cols;
    for (int i = 0; i < total; i++) {
        void* sum = A->field->add(A->data[i], B->data[i]);
        A->field->freeValue(C->data[i]); // освободим ноль
        C->data[i] = sum;
    }
    return C;
}

Matrix* mulMatrix(const Matrix* A, const Matrix* B, ErrorCode* err) {
    *err = MakeError(ERROR_NONE, "OK");
    if (A->field != B->field) {
        *err = MakeError(ERROR_TYPE, "Разные типы");
        return NULL;
    }
    if (A->cols != B->rows) {
        *err = MakeError(ERROR_DIM, "Несовместимые размеры при умножении");
        return NULL;
    }
    Matrix* C = createMatrix(A->rows, B->cols, A->field);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            void* acc = A->field->createZero();
            for (int k = 0; k < A->cols; k++) {
                void* mval = A->field->mul(
                    A->data[i * A->cols + k],
                    B->data[k * B->cols + j]
                );
                void* newAcc = A->field->add(acc, mval);
                A->field->freeValue(acc);
                A->field->freeValue(mval);
                acc = newAcc;
            }
            int idx = i * C->cols + j;
            A->field->freeValue(C->data[idx]);
            C->data[idx] = acc;
        }
    }
    return C;
}

Matrix* mulMatrixByScalar(const Matrix* A, double scalar, ErrorCode* err) {
    *err = MakeError(ERROR_NONE, "OK");
    Matrix* C = createMatrix(A->rows, A->cols, A->field);
    int total = A->rows * A->cols;
    for (int i = 0; i < total; i++) {
        void* val = A->field->mulScalar(A->data[i], scalar);
        A->field->freeValue(C->data[i]);
        C->data[i] = val;
    }
    return C;
}
