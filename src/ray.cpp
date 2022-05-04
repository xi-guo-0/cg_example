#include "ray.h"
Ray::Ray(Vec3d origin, Vec3d direction)
    : origin_(origin), direction_(direction) {
}

Vec3d Ray::Evaluate(double t) {
    return origin_ + (direction_ * t);
}
const Vec3d &Ray::Origin() const {
    return origin_;
}
const Vec3d &Ray::Direction() const {
    return direction_;
}
