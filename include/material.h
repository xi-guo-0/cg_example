#ifndef CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_
#define CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_

#include <Eigen/Dense>
#include <color.h>

class Material {
public:
    Material(Color color, double reflectance, double k_specular, double p);
    Color Evaluate(const Eigen::Vector3d &l, const Eigen::Vector3d &v,
                   const Eigen::Vector3d &n) const;

private:
    double reflectance_over_pi_;
    double k_specular_;
    double p_;
    Color color_;
};


#endif//CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_
