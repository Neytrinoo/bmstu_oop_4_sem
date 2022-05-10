#include <iostream>

#include "request.h"
#include "request_actions.h"


errorCode doRequest(Request &request, actions action) {
    static Shape shape = initShape();
    errorCode result = errorCode::SUCCESS;

    switch (action) {
    case actions::LOAD_FIGURE:
        result = readShapeFromFile(shape, request.filename_);
        break;
    case actions::DRAW_FIGURE:
        result = drawShapeOnCanvas(request.canvas_, shape);
        break;
    case actions::TRANSFER_FIGURE:
        result = transferShape(shape, request.transformAction_.ts);
        break;
    case actions::SCALE_FIGURE:
        result = scaleShape(shape, request.transformAction_.ss);
        break;
    case actions::ROTATE_FIGURE:
        result = rotateShape(shape, request.transformAction_.rs);
        break;
    case actions::SAVE_FIGURE_AT_FILE:
        result = writeShapeIntoFile(request.filename_, shape);
        break;
    case actions::SET_ROTATE_CENTER_IN_SHAPE_CENTER:
        interceptionRotateCenter(request.transformAction_.rs, shape);
        break;
    case actions::SET_SCALE_CENTER_IN_SHAPE_CENTER:
        interceptionScaleCenter(request.transformAction_.ss, shape);
        break;
    case actions::QUIT:
        result = quit(shape);
        break;
    default:
        result = errorCode::INVALID_ACTION;
    }

    return result;
}


void interceptionRotateCenter(RotateSettings &rs, const Shape &shape) {
    rs.center_ = shape.center_;
}


void interceptionScaleCenter(ScaleSettings &ss, const Shape &shape) {
    ss.center_ = shape.center_;
}
