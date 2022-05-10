#ifndef ERRORS_H
#define ERRORS_H

enum class errorCode {
    SUCCESS,
    NULL_POINTER_ERR,
    FILE_OPEN_ERR,
    INVALID_FILE,
    MEMORY_ALLOCATE_ERR,

    INVALID_ACTION,
};


const char *getErrorMessage(errorCode err);

void showErrorMessage(errorCode err);

#endif // ERRORS_H
