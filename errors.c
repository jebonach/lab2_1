#include "errors.h"
#include <stdio.h>
#include <string.h>


ErrorCode MakeError(int code, const char* msg) {
    ErrorCode e;
    e.code = code;
    strncpy(e.message, msg, sizeof(e.message)-1);
    e.message[sizeof(e.message)-1] = '\0';
    return e;
}

int IsOk(const ErrorCode* err) {
    return (err->code == ERROR_NONE);
}

void PrintError(const ErrorCode* err) {
    if (err->code != ERROR_NONE) {
        printf("Error %d: %s\n", err->code, err->message);
    }
}
