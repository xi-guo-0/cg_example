#ifndef CG_EXAMPLE_SRC_COLOR_H_
#define CG_EXAMPLE_SRC_COLOR_H_

#include <Eigen/Dense>
#include <cassert>
#include <cmath>
#include <iostream>

class Color {
public:
    double r;
    double g;
    double b;
    double a;


    Color(double r, double g, double b, double a)
        : r(std::clamp(r, 0.0, 1.0)), g(std::clamp(g, 0.0, 1.0)),
          b(std::clamp(b, 0.0, 1.0)), a(std::clamp(a, 0.0, 1.0)) {
    }

    Color() : Color(0, 0, 0, 0) {
    }

    explicit Color(const Eigen::Vector3d &vec)
        : Color(vec(0), vec(1), vec(2), 1.0) {
    }
    double operator[](int i) const {
        if (0 == i) {
            return r;
        } else if (1 == i) {
            return g;
        } else if (2 == i) {
            return b;
        } else {
            return a;
        }
    }
};


#endif//CG_EXAMPLE_SRC_COLOR_H_
