#include "shape.h"
#include "errors.h"

Shape initShape() {
    Shape shape;
    shape.points_ = nullptr;
    shape.lines_ = nullptr;

    return shape;
}

Shape createCopyShape(Shape &shape) {
    Shape copy = initShape();
    copy.center_ = shape.center_;
    copy.count_lines_ = shape.count_lines_;
    copy.count_points_ = shape.count_points_;

    copy.points_ = new Point[copy.count_points_];
    copy.lines_ = new Line[copy.count_points_];

    for (int i = 0; i < copy.count_points_; ++i) {
        copy.points_[i] = shape.points_[i];
    }

    for (int i = 0; i < copy.count_lines_; ++i) {
        copy.lines_[i] = shape.lines_[i];
    }

    return copy;
}

Point initPoint(double x, double y, double z) {
    return Point {x, y, z};
}

void freeShape(Shape &shape) {
    if (shape.points_ != nullptr) {
        delete[] shape.points_;
        shape.points_ = nullptr;
    }
    if (shape.lines_ != nullptr) {
        delete[] shape.lines_;
        shape.lines_ = nullptr;
    }
}

errorCode printShape(FILE *file, Shape &shape) {
    if (file == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    fprintf(file, "%d\n", shape.count_points_);
    for (int i = 0; i < shape.count_points_; ++i) {
        fprintf(file, "%lf %lf %lf\n", getX(shape.points_[i]), getY(shape.points_[i]), getZ(shape.points_[i]));
    }

    fprintf(file, "%d\n", shape.count_lines_);
    for (int i = 0; i < shape.count_lines_; ++i) {
        fprintf(file, "%d %d\n", getP1(shape.lines_[i]), getP2(shape.lines_[i]));
    }

    return errorCode::SUCCESS;
}

errorCode readShape(Shape &shape, FILE *file) {
    if (file == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    errorCode result_code = errorCode::SUCCESS;

    result_code = readPoints(&shape.points_, shape.count_points_, file);
    if (result_code == errorCode::SUCCESS) {
        setShapeCenter(shape);

        result_code = readLines(&shape.lines_, shape.count_lines_, file);

        if (result_code != errorCode::SUCCESS) {
            delete []shape.points_;
        }
    }

    if (result_code == errorCode::SUCCESS && !isValidLines(shape.lines_, shape.count_lines_, shape.count_points_)) {
        result_code = errorCode::INVALID_FILE;
        freeShape(shape);
    }

    return result_code;
}


errorCode readShapeSafe(Shape &shape, FILE *file) {
    if (file == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    Shape copy_shape;

    errorCode result_code = readShape(copy_shape, file);

    if (result_code == errorCode::SUCCESS) {
        freeShape(shape);
        shape = copy_shape;
    }

    return result_code;
}


errorCode readPoints(Point **points, int &count_points, FILE *file) {
    if (points == nullptr || file == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    errorCode err = readCount(count_points, file);

    if (err == errorCode::SUCCESS) {
        *points = new Point[count_points];
        if (points == nullptr) {
            err = errorCode::MEMORY_ALLOCATE_ERR;
        }
    }

    if (err == errorCode::SUCCESS) {
        bool valid_flag = true;

        for (int i = 0; valid_flag && i < count_points; ++i) {
            valid_flag = readPoint((*points)[i], file) == errorCode::SUCCESS;
        }

        if (!valid_flag) {
            delete[] *points;
            points = nullptr;
            err = errorCode::INVALID_FILE;
        }
    }

    return err;
}

errorCode readCount(int &count, FILE *file) {
    errorCode err = errorCode::SUCCESS;
    if (fscanf(file, "%d", &count) != 1 || count <= 0) {
        err = errorCode::INVALID_FILE;
    }

    return err;
}

bool isValidLines(Line *lines, const int count_lines, const int count_points) {
    bool valid_flag = true;
    for (int i = 0; valid_flag && i < count_lines; ++i) {
        valid_flag = lines[i].p1_ >= 0 && lines[i].p2_ >= 0 && lines[i].p1_ < count_points && lines[i].p2_ < count_points;
    }

    return valid_flag;
}

errorCode readLines(Line **lines, int &count_lines, FILE *file) {
    if (lines == nullptr || file == nullptr) {
        return errorCode::NULL_POINTER_ERR;
    }

    errorCode err = readCount(count_lines, file);

    if (err == errorCode::SUCCESS) {
        *lines = new Line[count_lines];
        if (lines == nullptr) {
            err = errorCode::MEMORY_ALLOCATE_ERR;
        }
    }

    if (err == errorCode::SUCCESS) {
        bool valid_flag = true;

        for (int i = 0; valid_flag && i < count_lines; ++i) {
            valid_flag = readLine((*lines)[i], file) == errorCode::SUCCESS;
        }

        if (!valid_flag) {
            delete[] lines;
            lines = nullptr;
            err = errorCode::INVALID_FILE;
        }
    }

    return err;
}


errorCode readPoint(Point &point, FILE *file) {
    int result = fscanf(file, "%lf %lf %lf", &point.x_, &point.y_, &point.z_);

    return result == 3 ? errorCode::SUCCESS : errorCode::INVALID_FILE;
}


errorCode readLine(Line &line, FILE *file) {
    int result = fscanf(file, "%d%d", &line.p1_, &line.p2_);
    if (result != 2) {
        return errorCode::INVALID_FILE;
    }

    return errorCode::SUCCESS;
}

void setShapeCenter(Shape &shape) {
    double min_x, max_x, min_y, max_y, min_z, max_z;

    for (int i = 0; i < shape.count_points_; ++i) {
        setMinMax(getX(shape.points_[i]), min_x, max_x);
        setMinMax(getY(shape.points_[i]), min_y, max_y);
        setMinMax(getZ(shape.points_[i]), min_z, max_z);
    }

    setX(shape.center_, min_x + (max_x - min_x) / 2);
    setY(shape.center_, min_y + (max_y - min_y) / 2);
    setZ(shape.center_, min_z + (max_z - min_z) / 2);
}


void setMinMax(double val, double &min, double &max) {
    if (val < min) {
        min = val;
    }
    if (val > max) {
        max = val;
    }
}


double getX(const Point &point) {
    return point.x_;
}


double getY(const Point &point) {
    return point.y_;
}


double getZ(const Point &point) {
    return point.z_;
}


void setX(Point &point, double val) {
    point.x_ = val;
}


void setY(Point &point, double val) {
    point.y_ = val;
}


void setZ(Point &point, double val) {
    point.z_ = val;
}


int getP1(const Line &line) {
    return line.p1_;
}


int getP2(const Line &line) {
    return line.p2_;
}

