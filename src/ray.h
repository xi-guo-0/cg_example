#ifndef CG_EXAMPLE_SRC_RAY_H_
#define CG_EXAMPLE_SRC_RAY_H_

#include "vec.h"

class Ray {
public:
    Ray(Vec3d origin, Vec3d direction);
    const Vec3d &Origin() const;
    const Vec3d &Direction() const;
    Vec3d Evaluate(double t);

private:
    Vec3d origin_;
    Vec3d direction_;
};


#endif//CG_EXAMPLE_SRC_RAY_H_
