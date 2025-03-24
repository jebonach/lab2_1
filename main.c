#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "interface.h"
#include "matrix.h"
#include "real.h"
#include "complex.h"

static void runTests() {
    FieldInfo* rf = GetRealFieldInfo();
    Matrix* A = createMatrix(2, 2, rf);
    Matrix* B = createMatrix(2, 2, rf);

    double valsA[4] = {1, 2, 3, 4};
    double valsB[4] = {5, 6, 7, 8};
    for (int i = 0; i < 4; i++) {
        rf->freeValue(A->data[i]);
        rf->freeValue(B->data[i]);
        double* va = (double*)malloc(sizeof(double));
        double* vb = (double*)malloc(sizeof(double));
        *va = valsA[i];
        *vb = valsB[i];
        A->data[i] = va;
        B->data[i] = vb;
    }

    ErrorCode err = 0;
    Matrix* C = addMatrix(A, B, &err);
    assert(err == 0 && C != NULL);
    double cExpectedAdd[4] = {6, 8, 10, 12};
    for (int i = 0; i < 4; i++) {
        double got = *((double*)C->data[i]);
        assert(got == cExpectedAdd[i]);
    }
    freeMatrix(C);

    C = mulMatrix(A, B, &err);
    assert(err == 0 && C != NULL);
    double cExpectedMul[4] = {19, 22, 43, 50};
    for (int i = 0; i < 4; i++) {
        double got = *((double*)C->data[i]);
        assert(got == cExpectedMul[i]);
    }
    freeMatrix(C);
    freeMatrix(A);
    freeMatrix(B);

    printf("Тесты прошли успешно!\n");
}

int main() {
    runTests();
    runInterface();
    return 0;
}
