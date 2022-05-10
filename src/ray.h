#ifndef CG_EXAMPLE_SRC_RAY_H_
#define CG_EXAMPLE_SRC_RAY_H_

#include "vec.h"

class Ray {
public:
    const Vec3d origin_;
    const Vec3d direction_;
    Ray(Vec3d origin, Vec3d direction);
    Vec3d At(double t) const;
};


#endif//CG_EXAMPLE_SRC_RAY_H_
