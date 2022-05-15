#include <material.h>
Material::Material(Color color) : color_(color) {
}
Color Material::Evaluate(const Eigen::Vector3d &l, const Eigen::Vector3d &v,
                         const Eigen::Vector3d &n) const {
    Eigen::Vector3d h = l + v;
    return color_ * std::max(0.0, n.dot(h));
}
