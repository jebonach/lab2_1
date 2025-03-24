#ifndef ERRORS_H
#define ERRORS_H

// Коды ошибок, которые могут возникнуть при работе с матрицами и вводом:
// - ERROR_NONE:     всё в порядке
// - ERROR_DIM:      несовместимые размеры
// - ERROR_TYPE:     несовместимые "поля" (FieldInfo), например, пытаемся сложить
//                 матрицы разных типов (вещественная и комплексная)
// - ERROR_INPUT:    ошибка ввода
// - ERROR_UNKNOWN:  любая неизвестная ошибка

typedef enum {
    ERROR_NONE = 0,
    ERROR_DIM,
    ERROR_TYPE,
    ERROR_INPUT,
    ERROR_UNKNOWN
} ErrorCode;

const char* GetErrorMessage(ErrorCode err);

#endif
