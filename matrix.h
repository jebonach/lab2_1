#ifndef MATRIX_H
#define MATRIX_H

#include "fieldinfo.h"
#include "errors.h"

typedef struct Matrix {
    int rows;
    int cols;
    void** data;
    FieldInfo* field;
} Matrix;

Matrix* createMatrix(int rows, int cols, FieldInfo* field);
void freeMatrix(Matrix* mat);

ErrorCode readMatrix(Matrix* mat);

void printMatrix(const Matrix* mat);

Matrix* addMatrix(const Matrix* A, const Matrix* B, ErrorCode* err);
Matrix* mulMatrix(const Matrix* A, const Matrix* B, ErrorCode* err);
Matrix* mulMatrixByScalar(const Matrix* A, double scalar, ErrorCode* err);

#endif