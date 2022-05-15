#include <light.h>

#include <utility>

PointLight::PointLight(Color I, Eigen::Vector3d p)
    : I_(std::move(I)), p_(std::move(p)) {
}

Color PointLight::Illuminate(const Ray &ray, const HitRecord &hrec) const {
    Eigen::Vector3d L = (p_ - hrec.point_);
    double r = L.norm();
    Eigen::Vector3d l = L.normalized();
    Eigen::Vector3d n = hrec.normal_;
    Color E = std::max(0.0, n.dot(l)) * I_ / r / r;
    Color k = hrec.material_->Evaluate(l, -ray.direction_, n);
    return k * E;
}
