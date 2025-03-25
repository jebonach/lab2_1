#ifndef ERRORS_H
#define ERRORS_H

enum {
    ERROR_NONE = 0,
    ERROR_DIM,
    ERROR_TYPE,
    ERROR_UNKNOWN
};

typedef struct {
    int code;
    char message[128];
} ErrorCode;

ErrorCode MakeError(int code, const char* msg);
int IsOk(const ErrorCode* err);
void PrintError(const ErrorCode* err);

#endif
