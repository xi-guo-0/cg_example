#ifndef CGEXAMPLE_INCLUDE_MESH_H_
#define CGEXAMPLE_INCLUDE_MESH_H_

#include <Eigen/Dense>
#include <string>
#include <vector>

class Mesh {
public:
    Mesh(const std::string &filename);

    int nverts() const;

    int nfaces() const;

    Eigen::Vector3d normal(const int iface, const int nthvert) const;

    Eigen::Vector3d vert(const int i) const;

    Eigen::Vector3d vert(const int iface, const int nthvert) const;

    Eigen::Vector2d uv(const int iface, const int nthvert) const;

private:
    std::vector<Eigen::Vector3d> verts;
    std::vector<Eigen::Vector3d> norms;
    std::vector<Eigen::Vector2d> tex_coord;
    std::vector<int> facet_vrt;
    std::vector<int> facet_tex;
    std::vector<int> facet_nrm;
};


#endif//CGEXAMPLE_INCLUDE_MESH_H_
