#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

static FieldInfo* COMPLEX_FIELD_INFO = NULL;

static Complex* newComplex(double re, double im) {
    Complex* c = (Complex*)malloc(sizeof(Complex));
    c->re = re;
    c->im = im;
    return c;
}

static void* complex_createZero() {
    return newComplex(0.0, 0.0);
}

static void complex_freeValue(void* value) {
    free(value);
}

static void* complex_readValue() {
    double re, im;
    if (scanf("%lf %lf", &re, &im) != 2) {
        re = 0.0;
        im = 0.0;
    }
    return newComplex(re, im);
}

static void complex_printValue(void* value) {
    Complex* c = (Complex*)value;
    printf("(%.2lf + %.2lfi)", c->re, c->im);
}

static void* complex_add(void* a, void* b) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    return newComplex(ca->re + cb->re, ca->im + cb->im);
}

static void* complex_mul(void* a, void* b) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    double re = ca->re * cb->re - ca->im * cb->im;
    double im = ca->re * cb->im + ca->im * cb->re;
    return newComplex(re, im);
}

static void* complex_mulScalar(void* a, double scalar) {
    Complex* c = (Complex*)a;
    return newComplex(c->re * scalar, c->im * scalar);
}



FieldInfo* GetComplexFieldInfo() {
    if (COMPLEX_FIELD_INFO == NULL) {
        COMPLEX_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));
        COMPLEX_FIELD_INFO->createZero = complex_createZero;
        COMPLEX_FIELD_INFO->freeValue = complex_freeValue;
        COMPLEX_FIELD_INFO->readValue = complex_readValue;
        COMPLEX_FIELD_INFO->printValue = complex_printValue;
        COMPLEX_FIELD_INFO->add = complex_add;
        COMPLEX_FIELD_INFO->mul = complex_mul;
        COMPLEX_FIELD_INFO->mulScalar = complex_mulScalar;
    }
    return COMPLEX_FIELD_INFO;
}
