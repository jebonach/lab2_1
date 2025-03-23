#ifndef MATRIX_H
#define MATRIX_H

#include "fieldinfo.h"

typedef struct Matrix {
    int size;
    void** data;
    FieldInfo* field;
} Matrix;

Matrix* createMatrix(int size, FieldInfo* field);
void    freeMatrix(Matrix* mat);
void    readMatrix(Matrix* mat);
void    printMatrix(Matrix* mat);

Matrix* addMatrix(const Matrix* A, const Matrix* B);
Matrix* mulMatrix(const Matrix* A, const Matrix* B);
Matrix* mulMatrixByScalar(const Matrix* A, double scalar);

#endif