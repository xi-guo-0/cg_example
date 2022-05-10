#ifndef CG_EXAMPLE_SRC_HITTABLE_H_
#define CG_EXAMPLE_SRC_HITTABLE_H_
#include "image.h"
#include "ray.h"
#include "vec.h"
#include <memory>
#include <variant>
#include <vector>

class HitRecord {
public:
    Vec3d point_;
    Vec3d normal_;
    double t_;
    bool front_face_;
    void SetFaceNormal(const Ray &ray, const Vec3d &outward_normal) {
        front_face_ = Dot(ray.direction_, (outward_normal)) < 0;
        normal_ = front_face_ ? outward_normal : -outward_normal;
    }
};

template<typename Hittable>
bool Hit(const Ray &ray, const Hittable &hittable, double t0, double t1,
         HitRecord *rec);

class Sphere {
public:
    const Vec3d center_;
    const double radius_;
    Sphere(Vec3d center, double radius) : center_(center), radius_(radius) {
    }
};

template<>
bool Hit(const Ray &ray, const Sphere &sphere, double t0, double t1,
         HitRecord *rec) {
    auto oc = ray.origin_ - sphere.center_;
    auto a = Dot(ray.direction_, ray.direction_);
    auto b = 2.0 * Dot(ray.direction_, oc);
    auto c = Dot(oc, oc) - sphere.radius_ * sphere.radius_;
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
    auto outward_normal = (rec->point_ - sphere.center_).Normalized();
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
