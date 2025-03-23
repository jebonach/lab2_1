#ifndef FIELDINFO_H
#define FIELDINFO_H

// Каждая функция, если возвращает результат, возвращает его как (void*).
// Это позволяет хранить в матрице элементы "любого" типа, при условии,
// что для этого типа определены все нужные операции.
 
// Добавить проверку при чтении, главное не забыть
typedef void* (*CreateZeroFunction)();
typedef void (*FreeValueFunction)(void* value);
typedef void* (*ReadValueFunction)();
typedef void (*PrintValueFunction)(void* value);
typedef void* (*AddFunction)(void* a, void* b);
typedef void* (*MulFunction)(void* a, void* b);
typedef void* (*MulScalarFunction)(void* a, double scalar);

typedef struct FieldInfo {
    CreateZeroFunction createZero;
    FreeValueFunction  freeValue;
    ReadValueFunction  readValue;
    PrintValueFunction printValue;
    AddFunction        add;
    MulFunction        mul;
    MulScalarFunction  mulScalar;
} FieldInfo;


// указатель на FI для вещественных чисел.
// real.c
 
FieldInfo* GetRealFieldInfo();

// указатель на FI для комплексных чисел.
// complex.c
FieldInfo* GetComplexFieldInfo();

#endif
