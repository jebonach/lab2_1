#include "errors.h"

const char* GetErrorMessage(ErrorCode err) {
    switch (err) {
        case ERROR_NONE: return "Нет ошибок";
        case ERROR_DIM: return "Несовместимые размеры матриц";
        case ERROR_TYPE: return "Несовместимые типы (разные FieldInfo)";
        case ERROR_INPUT: return "Ошибка при вводе";
        default: return "Неизвестная ошибка";
    }
}
