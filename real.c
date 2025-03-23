#include <stdio.h>
#include <stdlib.h>
#include "real.h"

static FieldInfo* REAL_FIELD_INFO = NULL;

static void* real_createZero() {
    double* zero = (double*)malloc(sizeof(double));
    *zero = 0.0;
    return zero;
}

static void real_freeValue(void* value) {
    free(value);
}

static void* real_readValue() {
    double* val = (double*)malloc(sizeof(double));
    if (scanf("%lf", val) != 1) {
        *val = 0.0;
    }
    return val;
}

static void real_printValue(void* value) {
    double* val = (double*)value;
    printf("%.4lf", *val);
}

static void* real_add(void* a, void* b) {
    double* da = (double*)a;
    double* db = (double*)b;
    double* res = (double*)malloc(sizeof(double));
    *res = (*da) + (*db);
    return res;
}

static void* real_mul(void* a, void* b) {
    double* da = (double*)a;
    double* db = (double*)b;
    double* res = (double*)malloc(sizeof(double));
    *res = (*da) * (*db);
    return res;
}

static void* real_mulScalar(void* a, double scalar) {
    double* da = (double*)a;
    double* res = (double*)malloc(sizeof(double));
    *res = (*da) * scalar;
    return res;
}



FieldInfo* GetRealFieldInfo() {
    if (REAL_FIELD_INFO == NULL) {
        REAL_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));
        REAL_FIELD_INFO->createZero = real_createZero;
        REAL_FIELD_INFO->freeValue = real_freeValue;
        REAL_FIELD_INFO->readValue = real_readValue;
        REAL_FIELD_INFO->printValue = real_printValue;
        REAL_FIELD_INFO->add = real_add;
        REAL_FIELD_INFO->mul = real_mul;
        REAL_FIELD_INFO->mulScalar = real_mulScalar;
    }
    return REAL_FIELD_INFO;
}
