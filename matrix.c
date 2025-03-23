#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

Matrix* createMatrix(int size, FieldInfo* field) {
    assert(size > 0);
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->size = size;
    mat->field = field;
    mat->data = (void**)malloc(size * size * sizeof(void*));

    for (int i = 0; i < size*size; i++) {
        mat->data[i] = field->createZero();
    }
    return mat;
}

void freeMatrix(Matrix* mat) {
    if (!mat) return;
    for (int i = 0; i < mat->size * mat->size; i++) {
        mat->field->freeValue(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void readMatrix(Matrix* mat) {
    for (int i = 0; i < mat->size * mat->size; i++) {
        mat->field->freeValue(mat->data[i]);
        mat->data[i] = mat->field->readValue();
    }
}

void printMatrix(Matrix* mat) {
    for (int i = 0; i < mat->size; i++) {
        for (int j = 0; j < mat->size; j++) {
            mat->field->printValue(mat->data[i * mat->size + j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* addMatrix(const Matrix* A, const Matrix* B) {
    assert(A->size == B->size);
    assert(A->field == B->field);
    int size = A->size;
    Matrix* C = createMatrix(size, A->field);

    for (int i = 0; i < size*size; i++) {
        void* sum = A->field->add(A->data[i], B->data[i]);
        A->field->freeValue(C->data[i]);
        C->data[i] = sum;
    }
    return C;
}

Matrix* mulMatrix(const Matrix* A, const Matrix* B) {
    assert(A->size == B->size);
    assert(A->field == B->field);
    int size = A->size;
    Matrix* C = createMatrix(size, A->field);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            void* acc = A->field->createZero();

            for (int k = 0; k < size; k++) {
                void* tmp = A->field->mul(A->data[i*size + k], B->data[k*size + j]);
                void* acc_new = A->field->add(acc, tmp);

                A->field->freeValue(acc);
                A->field->freeValue(tmp);

                acc = acc_new;
            }
            A->field->freeValue(C->data[i*size + j]);
            C->data[i*size + j] = acc;
        }
    }
    return C;
}

Matrix* mulMatrixByScalar(const Matrix* A, double scalar) {
    int size = A->size;
    Matrix* C = createMatrix(size, A->field);
    for (int i = 0; i < size*size; i++) {
        void* tmp = A->field->mulScalar(A->data[i], scalar);
        A->field->freeValue(C->data[i]);
        C->data[i] = tmp;
    }
    return C;
}
