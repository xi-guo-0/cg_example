#ifndef CG_EXAMPLE_SRC_HITTABLE_H_
#define CG_EXAMPLE_SRC_HITTABLE_H_
#include "color.h"
#include "image.h"
#include "ray.h"
#include <Eigen/Dense>
#include <memory>
#include <variant>
#include <vector>

class HitRecord {
private:
    using T = Eigen::Vector3d;

public:
    T point_;
    T normal_;
    double t_;
    bool front_face_;
    void SetFaceNormal(const Ray &ray, const T &outward_normal) {
        front_face_ = ray.direction_.dot(outward_normal) < 0;
        normal_ = front_face_ ? outward_normal : -outward_normal;
    }
};

template<typename Hittable>
bool Hit(const Ray &ray, const Hittable &hittable, double t0, double t1,
         HitRecord *rec);

class Sphere {
private:
    using T = Eigen::Vector3d;

public:
    const T center_;
    const double radius_;
    Sphere(T center, double radius) : center_(center), radius_(radius) {
    }
};

template<>
bool Hit(const Ray &ray, const Sphere &sphere, double t0, double t1,
         HitRecord *rec) {
    auto oc = ray.origin_ - sphere.center_;
    auto a = ray.direction_.dot(ray.direction_);
    auto b = 2.0 * ray.direction_.dot(oc);
    auto c = oc.dot(oc) - sphere.radius_ * sphere.radius_;
    double delta = b * b - 4 * a * c;
    if (delta < 0.0) {
        return false;
    }
    auto root = (-b - sqrt(delta)) / a / 2.0;
    if (root < t0 || t1 <= root) {
        root = (-b + sqrt(delta)) / a / 2.0;
        if (root < t0 || t1 <= root) {
            return false;
        }
    }
    rec->t_ = root;
    rec->point_ = ray.At(rec->t_);
    auto outward_normal = (rec->point_ - sphere.center_).normalized();
    rec->SetFaceNormal(ray, outward_normal);
    return true;
}

template<typename Hittable>
bool Hit(const Ray &ray, const std::vector<Hittable> &hitables, double t0,
         double t1, HitRecord *rec) {
    HitRecord temp_rec;
    auto hit_anything = false;
    auto closest_so_far = t1;
    for (const auto &hittable: hitables) {
        if (Hit(ray, hittable, t0, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t_;
        }
    }
    *rec = temp_rec;
    return hit_anything;
}
#endif//CG_EXAMPLE_SRC_HITTABLE_H_
