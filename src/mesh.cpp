#include "mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

BspTree::Node::Node(Triangle triangle)
    : Node(std::move(triangle), nullptr, nullptr) {
}

BspTree::Node::Node(Triangle triangle, BspTree::Node *left,
                    BspTree::Node *right)
    : triangle_(std::move(triangle)), left_(left), right_(right) {
}

double BspTree::Node::f(const Eigen::Vector3d &p) const {
    return ((triangle_.b() - triangle_.a())
                    .cross(triangle_.c() - triangle_.a()))
            .dot(p - triangle_.a());
}

void BspTree::Node::Add(const Triangle &triangle) {
    const double e = 0.001;
    double fa = f(triangle.a());
    double fb = f(triangle.b());
    double fc = f(triangle.c());
    if (std::abs(fa) < e) { fa = 0.0; }
    if (std::abs(fb) < e) { fb = 0.0; }
    if (std::abs(fc) < e) { fc = 0.0; }

    if (fa <= 0.0 && fb <= 0.0 && fc <= 0.0) {
        if (nullptr == left_) {
            left_ = new Node(triangle);
        } else {
            left_->Add(triangle);
        }
    } else if (0.0 <= fa && 0.0 <= fb && 0.0 <= fc) {
        if (nullptr == right_) {
            right_ = new Node(triangle);
        } else {
            right_->Add(triangle);
        }
    } else {
        Eigen::Vector3d a = triangle.a();
        Eigen::Vector3d b = triangle.b();
        Eigen::Vector3d c = triangle.c();

        if (0.0 <= fa * fc) {
            std::swap(fb, fc);
            std::swap(b, c);
            std::swap(fa, fb);
            std::swap(a, b);
        }
        if (0.0 <= fb * fc) {
            std::swap(fa, fc);
            std::swap(a, c);
            std::swap(fa, fb);
            std::swap(a, b);
        }

        Eigen::Hyperplane<double, 3> plane =
                Eigen::Hyperplane<double, 3>::Through(
                        triangle_.a(), triangle_.b(), triangle_.c());
        Eigen::ParametrizedLine<double, 3> line0 =
                Eigen::ParametrizedLine<double, 3>::Through(a, c);
        Eigen::ParametrizedLine<double, 3> line1 =
                Eigen::ParametrizedLine<double, 3>::Through(b, c);
        double alpha = line0.intersection(plane);
        Eigen::Vector3d A = line0.pointAt(alpha);
        double beta = line1.intersection(plane);
        Eigen::Vector3d B = line1.pointAt(beta);
        Triangle t0(a, b, A, triangle.GetMaterial());
        Triangle t1(b, B, A, triangle.GetMaterial());
        Triangle t2(A, B, c, triangle.GetMaterial());
        if (0 <= fc) {
            if (nullptr == left_) {
                left_ = new Node(t0);
            } else {
                left_->Add(t0);
            }
            left_->Add(t1);
            if (nullptr == right_) {
                right_ = new Node(t2);
            } else {
                right_->Add(t2);
            }
        } else {
            if (nullptr == right_) {
                right_ = new Node(t0);
            } else {
                right_->Add(t0);
            }
            right_->Add(t1);
            if (nullptr == left_) {
                left_ = new Node(t2);
            } else {
                left_->Add(t2);
            }
        }
    }
}

BspTree::BspTree() : root(nullptr) {
}

BspTree::BspTree(Triangle triangle) : root(new Node(std::move(triangle))) {
}

void BspTree::Add(const Triangle &triangle) {
    if (nullptr == root) {
        root = new Node(triangle);
    } else {
        root->Add(triangle);
    }
}

Mesh::Mesh(const std::string &filename) {
    std::ifstream ifs(filename);
    if (ifs.fail()) { return; }
    std::string line;
    while (!ifs.eof()) {
        std::getline(ifs, line);
        std::istringstream iss(line);
        std::string classification;
        iss >> classification;
        if ("v" == classification) {
            Eigen::Vector3d v;
            iss >> v.x() >> v.y() >> v.z();
            verts.push_back(v);
        } else if ("vn" == classification) {
            Eigen::Vector3d n;
            iss >> n.x() >> n.y() >> n.z();
            norms.push_back(n.normalized());
        } else if ("vt" == classification) {
            Eigen::Vector2d uv;
            iss >> uv.x() >> uv.y();
            tex_coord.push_back(uv);
        } else if ("f" == classification) {
            int f;
            int cnt = 0;
            while (iss >> f) {
                facet_vrt.push_back(f - 1);
                ++cnt;
            }
            if (3 != cnt) {
                std::cerr
                        << "Error: the obj file is supposed to be triangulated"
                        << std::endl;
                ifs.close();
                return;
            }
        }
    }
}

int Mesh::nverts() const {
    return verts.size();
}

int Mesh::nfaces() const {
    return facet_vrt.size() / 3;
}

Eigen::Vector3d Mesh::normal(const int iface, const int nthvert) const {
    return norms[facet_nrm[iface * 3 + nthvert]];
}

Eigen::Vector3d Mesh::vert(const int i) const {
    return verts[i];
}

Eigen::Vector3d Mesh::vert(const int iface, const int nthvert) const {
    return verts[facet_vrt[iface * 3 + nthvert]];
}

Eigen::Vector2d Mesh::uv(const int iface, const int nthvert) const {
    return tex_coord[facet_tex[iface * 3 + nthvert]];
}
