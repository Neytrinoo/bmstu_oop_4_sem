#include "request_actions.h"
#include "system.h"
#include "drawing.h"
#include "transforms.h"


errorCode readShapeFromFile(Shape &shape, const char *filename) {
    FILE *f = openFile(filename);
    if (f == nullptr) {
        return errorCode::INVALID_FILE;
    }

    errorCode result = readShapeSafe(shape, f);
    fclose(f);

    return result;
}


errorCode drawShapeOnCanvas(Canvas &canvas, Shape &shape) {
    return drawShape(canvas, shape);
}


errorCode writeShapeIntoFile(const char *filename, Shape &shape) {
    FILE *f = createFile(filename);
    if (f == nullptr) {
        return errorCode::INVALID_FILE;
    }

    errorCode result = printShape(f, shape);
    fclose(f);

    return result;
}


errorCode quit(Shape &shape) {
    freeShape(shape);

    return errorCode::SUCCESS;
}
