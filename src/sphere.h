#ifndef CG_EXAMPLE_SRC_SPHERE_H_
#define CG_EXAMPLE_SRC_SPHERE_H_
#include "ray.h"
#include "vec.h"

class Sphere {
public:
    const Vec3d &Center() const;
    double Radius() const;
    Sphere(Vec3d center, double radius);
    bool Hit(const Ray &ray, double *t0) const;

private:
    Vec3d center_;
    double radius_;
};


#endif//CG_EXAMPLE_SRC_SPHERE_H_
