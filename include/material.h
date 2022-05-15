#ifndef CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_
#define CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_

#include <Eigen/Dense>
#include <color.h>

class Material {
public:
    Material(Color color);
    Color Evaluate(const Eigen::Vector3d &l, const Eigen::Vector3d &v,
                   const Eigen::Vector3d &n) const;

private:
    Color color_;
};


#endif//CGEXAMPLE_INCLUDE_MATERIAL_MATERIAL_H_
