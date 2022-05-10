#ifndef REQUEST_H
#define REQUEST_H

#include "drawing.h"
#include "transforms.h"
#include "errors.h"

enum class actions {
    LOAD_FIGURE,
    DRAW_FIGURE,
    TRANSFER_FIGURE,
    SCALE_FIGURE,
    ROTATE_FIGURE,
    SAVE_FIGURE_AT_FILE,
    SET_ROTATE_CENTER_IN_SHAPE_CENTER,
    SET_SCALE_CENTER_IN_SHAPE_CENTER,
    QUIT,
};

using filename_t = const char *;

struct Request {
    Canvas canvas_;
    filename_t filename_;
    union {
        TransferSettings ts;
        RotateSettings rs;
        ScaleSettings ss;
    } transformAction_;
};

errorCode doRequest(Request &request, actions action);

void interceptionRotateCenter(RotateSettings &rs, const Shape &shape);

void interceptionScaleCenter(ScaleSettings &ss, const Shape &shape);


#endif // REQUEST_H
