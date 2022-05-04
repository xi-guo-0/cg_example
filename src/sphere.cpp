#include "sphere.h"

const Vec3d &Sphere::Center() const {
    return center_;
}

double Sphere::Radius() const {
    return radius_;
}

Sphere::Sphere(const Vec3d center, const double radius)
    : center_(center), radius_(radius) {
}
bool Sphere::Hit(const Ray &ray, double *t0) const {
    const auto l = ray.Origin() - Center();
    const auto a = ray.Direction() * ray.Direction();
    const auto b = 2.0 * ray.Direction() * l;
    const auto c = l * l - Radius() * Radius();
    const double delta = b * b - 4 * a * c;
    if (delta < 0.0) {
        return false;
    }
    *t0 = (-b + sqrt(delta)) / a / 2.0;
    return true;
}
