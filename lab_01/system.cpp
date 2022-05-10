#include "system.h"


FILE *openFile(const char *filename) {
    return fopen(filename, "r");
}


FILE *createFile(const char *filename) {
    return fopen(filename, "w");
}
