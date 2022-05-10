#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include "errors.h"

struct Point {
    double x_, y_, z_;
};

struct Line { // содержит индексы 2-х точек, между которыми будет линия
    int p1_, p2_;
};

struct Shape {
    Point center_;
    Point *points_;
    Line *lines_;
    int count_points_;
    int count_lines_;
};

Shape initShape();

Shape createCopyShape(Shape &shape);

Point initPoint(double x, double y, double z);

void freeShape(Shape &shape);

errorCode readShapeSafe(Shape &shape, FILE *file);

errorCode printShape(FILE *file, Shape &shape);

errorCode readPoints(Point **points, int &count_points, FILE *file);

errorCode readLines(Line **lines, int &count_lines, FILE *file);

errorCode readPoint(Point &point, FILE *file);

errorCode readLine(Line &line, FILE *file);

errorCode readCount(int &count, FILE *file);

bool isValidLines(Line *lines, const int count_lines, const int count_points);

void setShapeCenter(Shape &shape);

void setMinMax(double val, double &min, double &max);

double getX(const Point &point);

double getY(const Point &point);

double getZ(const Point &point);

void setX(Point &point, double val);

void setY(Point &point, double val);

void setZ(Point &point, double val);

int getP1(const Line &line);

int getP2(const Line &line);

#endif // SHAPE_H
