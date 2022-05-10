#include <math.h>

#include "transforms.h"

double calculateTrigWithDegree(double (*trig_func)(double), const double degree) {
    double radians = degree * M_PI / 180;

    return trig_func(radians);
}


void rotateXPoint(Point &point, const double angle, const Point &center) {
    double tmp_y = point.y_;

    double cosinus = calculateTrigWithDegree(cos, angle);
    double sinus = calculateTrigWithDegree(sin, angle);

    point.y_ = center.y_ + (point.y_ - center.y_) * cosinus + (point.z_ - center.z_) * sinus;
    point.z_ = center.z_ + (point.z_ - center.z_) * cosinus - (tmp_y - center.y_) * sinus;
}


void rotateYPoint(Point &point, const double angle, const Point &center) {
    double tmp_x = point.x_;

    double cosinus = calculateTrigWithDegree(cos, angle);
    double sinus = calculateTrigWithDegree(sin, angle);

    point.x_ = center.x_ + (point.x_ - center.x_) * cosinus + (point.z_ - center.z_) * sinus;
    point.z_ = center.z_ + (point.z_ - center.z_) * cosinus - (tmp_x - center.x_) * sinus;
}


void rotateZPoint(Point &point, const double angle, const Point &center) {
    double tmp_x = point.x_;

    double cosinus = calculateTrigWithDegree(cos, angle);
    double sinus = calculateTrigWithDegree(sin, angle);

    point.x_ = center.x_ + (point.x_ - center.x_) * cosinus + (point.y_ - center.y_) * sinus;
    point.y_ = center.y_ + (point.y_ - center.y_) * cosinus - (tmp_x - center.x_) * sinus;
}


void transferPoint(Point &point, const TransferSettings &settings) {
    point.x_ += settings.dx_;
    point.y_ += settings.dy_;
    point.z_ += settings.dz_;
}


void rotatePoint(Point &point, const RotateSettings &settings) {
    rotateXPoint(point, settings.ax_, settings.center_);
    rotateYPoint(point, settings.ay_, settings.center_);
    rotateZPoint(point, settings.az_, settings.center_);
}


void scalePoint(Point &point, const ScaleSettings &settings) {
    point.x_ = point.x_ * settings.dx_ + (1 - settings.dx_) * getX(settings.center_);
    point.y_ = point.y_ * settings.dy_ + (1 - settings.dy_) * getY(settings.center_);
    point.z_ = point.z_ * settings.dz_ + (1 - settings.dz_) * getZ(settings.center_);
}


errorCode transferShape(Shape &shape, const TransferSettings &settings) {
    if (shape.points_ == nullptr || shape.count_points_ <= 0) {
        return errorCode::NULL_POINTER_ERR;
    }

    for (int i = 0; i < shape.count_points_; ++i) {
        transferPoint(shape.points_[i], settings);
    }

    transferPoint(shape.center_, settings);

    return errorCode::SUCCESS;
}


errorCode rotateShape(Shape &shape, const RotateSettings &settings) {
    if (shape.points_ == nullptr || shape.count_points_ <= 0) {
        return errorCode::NULL_POINTER_ERR;
    }

    for (int i = 0; i < shape.count_points_; ++i) {
        rotatePoint(shape.points_[i], settings);
    }

    rotatePoint(shape.center_, settings);

    return errorCode::SUCCESS;
}


errorCode scaleShape(Shape &shape, const ScaleSettings &settings) {
    if (shape.points_ == nullptr || shape.count_points_ <= 0) {
        return errorCode::NULL_POINTER_ERR;
    }

    for (int i = 0; i < shape.count_points_; ++i) {
        scalePoint(shape.points_[i], settings);
    }

    scalePoint(shape.center_, settings);

    return errorCode::SUCCESS;
}


TransferSettings initTransferSettings(double dx, double dy, double dz) {
    return TransferSettings{dx, dy, dz};
}


RotateSettings initRotateSettings(double ax, double ay, double az) {
    return RotateSettings{ax, ay, az, Point{0, 0, 0}};
}


ScaleSettings initScaleSettings(double dx, double dy, double dz) {
    return ScaleSettings{dx, dy, dz, Point{0, 0, 0}};
}
