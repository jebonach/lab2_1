#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

Matrix* createMatrix(int rows, int cols, FieldInfo* field) {
    assert(rows > 0 && cols > 0);
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows  = rows;
    mat->cols  = cols;
    mat->field = field;
    mat->data = (void**)malloc(rows * cols * sizeof(void*));

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
    return ERROR_NONE;
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
    *err = ERROR_NONE;

    if (A->field != B->field) {
        *err = ERROR_TYPE;
        return NULL;
    }

    if (A->rows != B->rows || A->cols != B->cols) {
        *err = ERROR_DIM;
        return NULL;
    }

    Matrix* C = createMatrix(A->rows, A->cols, A->field);
    int total = A->rows * A->cols;
    for (int i = 0; i < total; i++) {
        void* sum = A->field->add(A->data[i], B->data[i]);
        A->field->freeValue(C->data[i]);
        C->data[i] = sum;
    }
    return C;
}

Matrix* mulMatrix(const Matrix* A, const Matrix* B, ErrorCode* err) {
    *err = ERROR_NONE;
    if (A->field != B->field) {
        *err = ERROR_TYPE;
        return NULL;
    }
    if (A->cols != B->rows) {
        *err = ERROR_DIM;
        return NULL;
    }

    Matrix* C = createMatrix(A->rows, B->cols, A->field);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            void* acc = A->field->createZero();
            for (int k = 0; k < A->cols; k++) {
                void* mul = A->field->mul(
                    A->data[i * A->cols + k],
                    B->data[k * B->cols + j]
                );
                void* newAcc = A->field->add(acc, mul);
                A->field->freeValue(acc);
                A->field->freeValue(mul);
                acc = newAcc;
            }
            int indexC = i * C->cols + j;
            A->field->freeValue(C->data[indexC]);
            C->data[indexC] = acc;
        }
    }
    return C;
}

Matrix* mulMatrixByScalar(const Matrix* A, double scalar, ErrorCode* err) {
    *err = ERROR_NONE;
    Matrix* C = createMatrix(A->rows, A->cols, A->field);
    int total = A->rows * A->cols;
    for (int i = 0; i < total; i++) {
        void* val = A->field->mulScalar(A->data[i], scalar);
        A->field->freeValue(C->data[i]);
        C->data[i] = val;
    }
    return C;
}
