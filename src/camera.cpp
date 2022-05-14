#include "camera.h"

#include <utility>
Camera::Camera(Eigen::Vector3d origin, Eigen::Vector3d horizontal,
               Eigen::Vector3d vertical, double focal_length)
    : origin_(std::move(origin)), horizontal_(std::move(horizontal)),
      vertical_(std::move(vertical)) {
    to_lower_left_corner_ =
            -horizontal_ / 2.0 - vertical_ / 2.0 -
            (horizontal_.cross(vertical_).normalized() * focal_length);
}

Ray Camera::GetRay(double u, double v) const {
    return {origin_, to_lower_left_corner_ + u * horizontal_ + v * vertical_};
}
