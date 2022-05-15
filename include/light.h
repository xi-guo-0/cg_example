#ifndef CGEXAMPLE_INCLUDE_LIGHT_LIGHT_H_
#define CGEXAMPLE_INCLUDE_LIGHT_LIGHT_H_

#include <hittable.h>
#include <ray.h>

class Light {
public:
    virtual Color Illuminate(const Ray &ray, const HitRecord &hrec) const = 0;
};

class PointLight : public Light {
public:
    PointLight(Color I, Eigen::Vector3d p);
    Color Illuminate(const Ray &ray, const HitRecord &hrec) const override;

private:
    const Color I_;
    const Eigen::Vector3d p_;
};

#endif//CGEXAMPLE_INCLUDE_LIGHT_LIGHT_H_
