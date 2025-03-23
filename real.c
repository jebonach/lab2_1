#include <stdio.h>
#include <stdlib.h>
#include "real.h"

static FieldInfo* REAL_FIELD_INFO = NULL;

static void* real_createZero() {
    double* zero = malloc(sizeof(double));
    *zero = 0.0;
    return zero;
}

static void real_freeValue(void* value) {
    free(value);
}


static void* real_readValue() {
    double temp;
    while (1) {
        int rc = scanf("%lf", &temp);
        if (rc == 1) {
            double* val = malloc(sizeof(double));
            *val = temp;
            return val;
        } else {
            printf("[Ошибка] Введите корректное вещественное число: ");
            while (getchar() != '\n') {}
        }
    }
}

static void real_printValue(void* value) {
    double* val = (double*)value;
    printf("%.4lf", *val);
}

static void* real_add(void* a, void* b) {
    double da = *((double*)a);
    double db = *((double*)b);
    double* res = malloc(sizeof(double));
    *res = da + db;
    return res;
}

static void* real_mul(void* a, void* b) {
    double da = *((double*)a);
    double db = *((double*)b);
    double* res = malloc(sizeof(double));
    *res = da * db;
    return res;
}

static void* real_mulScalar(void* a, double scalar) {
    double da = *((double*)a);
    double* res = malloc(sizeof(double));
    *res = da * scalar;
    return res;
}

FieldInfo* GetRealFieldInfo() {
    if (REAL_FIELD_INFO == NULL) {
        REAL_FIELD_INFO = malloc(sizeof(FieldInfo));
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
