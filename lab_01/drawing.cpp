#include "drawing.h"

errorCode drawShape(Canvas &canvas, Shape &shape) {
    errorCode result = errorCode::SUCCESS;
    do {
        if (canvas.scene == nullptr) {
            result = errorCode::NULL_POINTER_ERR;
            break;
        }

        clearCanvas(canvas);

        result = drawShapePoints(canvas, shape);
        if (result != errorCode::SUCCESS) {
            break;
        }

        result =  drawShapeLines(canvas, shape);
        if (result != errorCode::SUCCESS) {
            break;
        }
    } while (false);

    return result;
}


errorCode drawShapePoints(Canvas &canvas, Shape &shape) {
    if (shape.points_ == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    for (int i = 0; i < shape.count_points_; ++i) {
        drawPoint(canvas, shape.points_[i]);
    }

    return errorCode::SUCCESS;
}


errorCode drawShapeLines(Canvas &canvas, Shape &shape) {
    if (shape.lines_ == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    for (int i = 0; i < shape.count_lines_; ++i) {
        drawLine(canvas, shape.points_[getP1(shape.lines_[i])], shape.points_[getP2(shape.lines_[i])]);
    }

    return errorCode::SUCCESS;
}


void drawLine(Canvas &canvas, const Point &point1, const Point &point2) {
    canvas.scene->addLine(point1.x_, point1.y_, point2.x_, point2.y_, QPen(Qt::blue, 2));
}


void drawPoint(Canvas &canvas, const Point &point) {
    canvas.scene->addEllipse(QRectF(point.x_, point.y_, 2, 2), QPen(Qt::red, 3));
}


void clearCanvas(Canvas &canvas) {
    if (canvas.scene != nullptr) {
        canvas.scene->clear();
    }
}
