#include "ray.h"
Ray::Ray(Vec3d origin, Vec3d direction)
    : origin_(origin), direction_(direction.Normalized()) {
}

Vec3d Ray::At(double t) const {
    return origin_ + (direction_ * t);
}
