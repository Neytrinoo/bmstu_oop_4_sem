#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "shape.h"
#include "errors.h"

struct TransferSettings {
    double dx_, dy_, dz_;
};

struct RotateSettings {
    double ax_, ay_, az_;
    Point center_;
};

struct ScaleSettings {
    double dx_, dy_, dz_;
    Point center_;
};


double calculateTrigWithDegree(double (*trig_func)(double), const double degree);

TransferSettings initTransferSettings(double dx, double dy, double dz);

RotateSettings initRotateSettings(double ax, double ay, double az);

ScaleSettings initScaleSettings(double dx, double dy, double dz);

void rotateXPoint(Point &point, const double angle, const Point &center);

void rotateYPoint(Point &point, const double angle, const Point &center);

void rotateZPoint(Point &point, const double angle, const Point &center);


void transferPoint(Point &point, const TransferSettings &settings);

void rotatePoint(Point &point, const RotateSettings &settings);

void scalePoint(Point &point, const ScaleSettings &settings);


errorCode transferShape(Shape &shape, const TransferSettings &settings);

errorCode rotateShape(Shape &shape, const RotateSettings &settings);

errorCode scaleShape(Shape &shape, const ScaleSettings &settings);

#endif // TRANSFORMS_H
