#ifndef CG_EXAMPLE_SRC_CAMERA_H_
#define CG_EXAMPLE_SRC_CAMERA_H_

#include "ray.h"
#include <Eigen/Dense>

class Camera {
public:
    Camera(Eigen::Vector3d origin, Eigen::Vector3d horizontal,
           Eigen::Vector3d vertical, double focal_length);

    Ray GetRay(double u, double v) const;

private:
    Eigen::Vector3d origin_;
    Eigen::Vector3d to_lower_left_corner_;
    Eigen::Vector3d horizontal_;
    Eigen::Vector3d vertical_;
};


#endif//CG_EXAMPLE_SRC_CAMERA_H_
