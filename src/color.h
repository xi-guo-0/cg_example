#ifndef CG_EXAMPLE_SRC_COLOR_H_
#define CG_EXAMPLE_SRC_COLOR_H_

#include <Eigen/Dense>
#include <cassert>
#include <cmath>
#include <iostream>

class Color {
public:
    double r_;
    double g_;
    double b_;
    double a_;


    Color(double r, double g, double b, double a) : r_(r), g_(g), b_(b), a_(a) {
    }

    Color() : Color(0, 0, 0, 0) {
    }

    explicit Color(const Eigen::Vector3d &vec)
        : Color(vec(0), vec(1), vec(2), 1.0) {
    }
    double operator[](int i) const {
        if (0 == i) {
            return r_;
        } else if (1 == i) {
            return g_;
        } else if (2 == i) {
            return b_;
        } else {
            return a_;
        }
    }
};


#endif//CG_EXAMPLE_SRC_COLOR_H_
