#ifndef REQUEST_ACTIONS_H
#define REQUEST_ACTIONS_H

#include "shape.h"
#include "errors.h"
#include "request.h"
#include "transforms.h"

errorCode readShapeFromFile(Shape &shape, const char *filename);

errorCode drawShapeOnCanvas(Canvas &canvas, Shape &shape);

errorCode writeShapeIntoFile(const char *filename, Shape &shape);

errorCode quit(Shape &shape);

#endif // REQUEST_ACTIONS_H
