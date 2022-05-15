#include <cmath>
#include <material.h>
#include <numbers>
Material::Material(Color color, double reflectance, double k_specular, double p)
    : color_(color), reflectance_over_pi_(reflectance / std::numbers::pi),
      k_specular_(k_specular), p_(p) {
}
Color Material::Evaluate(const Eigen::Vector3d &l, const Eigen::Vector3d &v,
                         const Eigen::Vector3d &n) const {
    Eigen::Vector3d h = l + v;
    return (reflectance_over_pi_ +
            k_specular_ * std::pow(std::max(0.0, n.dot(h)), p_)) *
           color_;
}
