#ifndef CG_EXAMPLE_SRC_HITTABLE_H_
#define CG_EXAMPLE_SRC_HITTABLE_H_
#include <Eigen/Dense>
#include <color.h>
#include <image.h>
#include <material.h>
#include <memory>
#include <ray.h>
#include <utility>
#include <variant>
#include <vector>

class HitRecord {
public:
    HitRecord()
        : material_(std::make_shared<Material>(Color(0, 0, 0, 1), 1.0, 1.0,
                                               1.0)) {
    }
    HitRecord(const HitRecord &other) = default;
    HitRecord &operator=(const HitRecord &other) {
        point_ = other.point_;
        normal_ = other.normal_;
        t_ = other.t_;
        front_face_ = other.front_face_;
        material_ = other.material_;
        return *this;
    };
    Eigen::Vector3d point_;
    Eigen::Vector3d normal_;
    double t_;
    bool front_face_;
    std::shared_ptr<Material> material_;
    void SetFaceNormal(const Ray &ray, const Eigen::Vector3d &outward_normal) {
        Eigen::Vector3d outward = outward_normal.normalized();
        front_face_ = ray.direction_.dot(outward) < 0;
        normal_ = front_face_ ? outward : -outward;
    }
};


class Hittable {
public:
    virtual bool Hit(const Ray &ray, double t0, double t1,
                     HitRecord *hrec) const = 0;
};

class HitElement : public Hittable {
public:
    explicit HitElement(std::shared_ptr<Material> material);
    std::shared_ptr<Material> GetMaterial() const;

protected:
    const std::shared_ptr<Material> material_;
};

class Sphere : public HitElement {
public:
    Sphere(Eigen::Vector3d center, double radius,
           std::shared_ptr<Material> material);

    const Eigen::Vector3d &GetCenter() const;

    double GetRadius() const;


    bool Hit(const Ray &ray, double t0, double t1,
             HitRecord *hrec) const override;

private:
    const Eigen::Vector3d center_;
    const double radius_;
};


class Triangle : public HitElement {
public:
    Triangle(Eigen::Vector3d a, Eigen::Vector3d b, Eigen::Vector3d c,
             std::shared_ptr<Material> material);
    const Eigen::Vector3d &a() const;
    const Eigen::Vector3d &b() const;
    const Eigen::Vector3d &c() const;
    bool Hit(const Ray &ray, double t0, double t1,
             HitRecord *hrec) const override;

private:
    const Eigen::Vector3d a_;
    const Eigen::Vector3d b_;
    const Eigen::Vector3d c_;
};

class HitList : public Hittable {
public:
    void add(std::shared_ptr<Hittable> &hittable);
    bool Hit(const Ray &ray, double t0, double t1,
             HitRecord *hrec) const override;

private:
    std::vector<std::shared_ptr<Hittable>> hit_list_;
};

#endif//CG_EXAMPLE_SRC_HITTABLE_H_
