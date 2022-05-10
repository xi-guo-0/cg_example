#ifndef CG_EXAMPLE_SRC_VEC_H_
#define CG_EXAMPLE_SRC_VEC_H_

#include <cassert>
#include <cmath>
#include <iostream>

template<typename T, int n>
struct Vec {

    Vec() = default;

    T &operator[](const int i) {
        assert(0 <= i && i < n);
        return data[i];
    }

    T operator[](const int i) const {
        assert(0 <= i && i < n);
        return data[i];
    }

    T norm2() const {
        return Dot(*this, *this);
    }

    T norm() const {
        return std::sqrt(norm2());
    }

    T data[n]{};
};

template<typename T, int n>
T Dot(const Vec<T, n> &lhs, const Vec<T, n> &rhs) {
    T ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += lhs[i] * rhs[i];
    }
    return ans;
}

template<typename T, int n>
Vec<T, n> operator-(const Vec<T, n> &ary) {
    auto ans = ary;
    for (int i = 0; i < n; ++i) {
        ans[i] = -ans[i];
    }
    return ans;
}

template<typename T, int n>
Vec<T, n> operator+(const Vec<T, n> &lhs, const Vec<T, n> &rhs) {
    Vec<T, n> ans = lhs;
    for (int i = 0; i < n; ++i) {
        ans[i] += rhs[i];
    }
    return ans;
}
template<typename T, int n>
Vec<T, n> operator-(const Vec<T, n> &lhs, const Vec<T, n> &rhs) {
    Vec<T, n> ans = lhs;
    for (int i = 0; i < n; ++i) {
        ans[i] -= rhs[i];
    }
    return ans;
}

template<typename T, int n>
Vec<T, n> operator*(const Vec<T, n> &lhs, const T rhs) {
    Vec<T, n> ans = lhs;
    for (int i = 0; i < n; ++i) {
        ans[i] *= rhs;
    }
    return ans;
}

template<typename T, int n>
Vec<T, n> operator*(const T lhs, const Vec<T, n> &rhs) {
    return rhs * lhs;
}

template<typename T, int n>
Vec<T, n> operator/(const Vec<T, n> &lhs, const T rhs) {
    Vec<T, n> ans = lhs;
    for (int i = 0; i < n; ++i) {
        ans[i] /= rhs;
    }
    return ans;
}


template<typename T, int n>
std::ostream &operator<<(std::ostream &out, const Vec<T, n> &v) {
    for (int i = 0; i < n; ++i) {
        out << v[i] << " ";
    }
    return out;
}

template<typename T, int n>
std::istream &operator>>(std::istream &in, Vec<T, n> &v) {
    for (int i = 0; i < n; ++i) {
        in >> v[i];
    }
    return in;
}

template<>
struct Vec<double, 3> {
    Vec() = default;
    Vec(double x, double y, double z) : x_(x), y_(y), z_(z) {
    }
    double &operator[](const int i) {
        assert(0 <= i && i < 3);
        return data_[i];
    }
    double operator[](const int i) const {
        assert(0 <= i && i < 3);
        return data_[i];
    }

    double norm2() const {
        return Dot(*this, *this);
    }
    double norm() const {
        return std::sqrt(norm2());
    }
    Vec Normalized() const {
        return *this / norm();
    }
    union {
        struct {
            double x_;
            double y_;
            double z_;
        };
        double data_[3];
    };
};

using Vec3f = Vec<float, 3>;
using Vec3d = Vec<double, 3>;

struct Color {
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

    explicit Color(const Vec3d &vec) : Color(vec.x_, vec.y_, vec.z_, 1.0) {
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


#endif//CG_EXAMPLE_SRC_VEC_H_
