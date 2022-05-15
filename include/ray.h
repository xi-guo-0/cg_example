#ifndef CG_EXAMPLE_SRC_RAY_H_
#define CG_EXAMPLE_SRC_RAY_H_

#include <Eigen/Dense>

class Ray {
private:
    using T = Eigen::Vector3d;

public:
    const T origin_;
    const T direction_;
    Ray(T origin, const T &direction);
    auto At(double t) const -> T;
};

#endif//CG_EXAMPLE_SRC_RAY_H_
