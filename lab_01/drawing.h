#ifndef DRAWING_H
#define DRAWING_H

#include <QGraphicsScene>

#include "shape.h"

// отвечает за отрисовку фигуры на экран. в MVC выступает в роли view

struct Canvas {
    QGraphicsScene *scene;
};

errorCode drawShape(Canvas &canvas, Shape &shape);

errorCode drawShapePoints(Canvas &canvas, Shape &shape);

errorCode drawShapeLines(Canvas &canvas, Shape &shape);

void drawLine(Canvas &canvas, const Point &point1, const Point &point2);

void drawPoint(Canvas &canvas, const Point &point);

void clearCanvas(Canvas &canvas);

#endif // DRAWING_H
