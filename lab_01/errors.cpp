#include <QMessageBox>

#include "errors.h"

const char *getErrorMessage(errorCode err) {
    const char *result = nullptr;
    switch (err) {
    case errorCode::SUCCESS:
        result = "All is good!";
        break;
    case errorCode::NULL_POINTER_ERR:
        result = "Null pointer error";
        break;
    case errorCode::FILE_OPEN_ERR:
        result = "Cannot open file";
        break;
    case errorCode::INVALID_FILE:
        result = "Invalid file";
        break;
    case errorCode::MEMORY_ALLOCATE_ERR:
        result = "Memory allocate error";
        break;
    case errorCode::INVALID_ACTION:
        result = "Invalid action";
        break;
    default:
        result = "Unexpected error";
    }

    return result;
}

void showErrorMessage(errorCode err) {
    QMessageBox::critical(nullptr, "Error", getErrorMessage(err));
}
