#include <ray.h>

#include <utility>
Ray::Ray(T origin, const T &direction)
    : origin_(std::move(origin)), direction_(direction.normalized()) {
}

auto Ray::At(double t) const -> T {
    return origin_ + (direction_ * t);
}
