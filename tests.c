#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"

#include "matrix.h"
#include "errors.h"
#include "real.h"
#include "complex.h"

static void test_addMatrix_2x2_real() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2,2,rf);
    Matrix* B = createMatrix(2,2,rf);

    double valsA[4] = {1,2,3,4};
    double valsB[4] = {5,6,7,8};
    for (int i=0; i<4; i++){
        double* va = malloc(sizeof(double));
        double* vb = malloc(sizeof(double));
        *va = valsA[i];
        *vb = valsB[i];
        A->data[i] = va;
        B->data[i] = vb;
    }

    ErrorCode err;
    Matrix* C = addMatrix(A, B, &err);
    assert(IsOk(&err));
    assert(C != NULL);

    double cExp[4] = {6,8,10,12};
    for (int i=0; i<4; i++){
        double got = *((double*)C->data[i]);
        assert(got == cExp[i]);
    }

    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    printf("test_addMatrix_2x2_real: OK\n");
}

static void test_addMatrix_dimMismatch() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2,2,rf);
    Matrix* B = createMatrix(3,2,rf);

    ErrorCode err;
    Matrix* C = addMatrix(A, B, &err);
    assert(C == NULL);
    assert(err.code == ERROR_DIM);

    freeMatrix(A);
    freeMatrix(B);
    printf("test_addMatrix_dimMismatch: OK\n");
}

static void test_addMatrix_typeMismatch() {
    FieldInfo* rf = GetRealFieldInfo();
    FieldInfo* cf = GetComplexFieldInfo();

    Matrix* A = createMatrix(2,2,rf);
    Matrix* B = createMatrix(2,2,cf);

    ErrorCode err;
    Matrix* C = addMatrix(A, B, &err);
    assert(C == NULL);
    assert(err.code == ERROR_TYPE);

    freeMatrix(A);
    freeMatrix(B);
    printf("test_addMatrix_typeMismatch: OK\n");
}

// Пример теста умножения
static void test_mulMatrix_dimMismatch() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2,3,rf);
    Matrix* B = createMatrix(2,2,rf);

    ErrorCode err;
    Matrix* C = mulMatrix(A, B, &err);
    assert(C == NULL);
    assert(err.code == ERROR_DIM);

    freeMatrix(A);
    freeMatrix(B);
    printf("test_mulMatrix_dimMismatch: OK\n");
}

static void test_mulMatrixByScalar() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2,2,rf);

    double vals[4] = {1,2,3,4};
    for(int i=0;i<4;i++){
        double* tmp = malloc(sizeof(double));
        *tmp = vals[i];
        A->data[i] = tmp;
    }

    ErrorCode err;
    Matrix* C = mulMatrixByScalar(A, 10.0, &err);
    assert(IsOk(&err));
    double cExp[4] = {10,20,30,40};
    for(int i=0;i<4;i++){
        double got = *((double*)C->data[i]);
        assert(got == cExp[i]);
    }

    freeMatrix(A);
    freeMatrix(C);
    printf("test_mulMatrixByScalar: OK\n");
}

void runAllTests() {
    test_addMatrix_2x2_real();
    test_addMatrix_dimMismatch();
    test_addMatrix_typeMismatch();
    test_mulMatrix_dimMismatch();
    test_mulMatrixByScalar();

    printf("\n=== Все тесты прошли успешно ===\n");
}
